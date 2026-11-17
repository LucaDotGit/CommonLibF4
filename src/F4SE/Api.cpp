#include "F4SE/Api.hpp"

#include "F4SE/Core.hpp"
#include "F4SE/DelayFunctorManager.hpp"
#include "F4SE/ISharedObjectFactoryList.hpp"
#include "F4SE/LoadInterface.hpp"
#include "F4SE/Menus/IMenuAssetLoaderMap.hpp"
#include "F4SE/Menus/IMenuInfoMap.hpp"
#include "F4SE/Menus/MenuAssetInfo.hpp"
#include "F4SE/Menus/MenuAssetLoader.hpp"
#include "F4SE/Menus/MenuInfo.hpp"
#include "F4SE/MessagingInterface.hpp"
#include "F4SE/ObjectInterface.hpp"
#include "F4SE/ObjectRegistry.hpp"
#include "F4SE/PapyrusInterface.hpp"
#include "F4SE/PersistentObjectStorage.hpp"
#include "F4SE/PluginInfo.hpp"
#include "F4SE/PluginVersionData.hpp"
#include "F4SE/PreLoadInterface.hpp"
#include "F4SE/QueryInterface.hpp"
#include "F4SE/ScaleformInterface.hpp"
#include "F4SE/SerializationInterface.hpp"
#include "F4SE/TaskInterface.hpp"
#include "F4SE/TrampolineInterface.hpp"
#include "F4SE/Translator.hpp"
#include "F4SE/Versions.hpp"
#include "RE/B/BSEventNotifyControl.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScaleformManager.hpp"
#include "RE/B/BSScaleformTranslator.hpp"
#include "RE/B/BSScriptUtility_StackErrorMessage.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_LogEvent.hpp"
#include "RE/B/BSScript_LogSeverity.hpp"
#include "RE/B/BSTEvent.hpp"
#include "REL/HookList.hpp"
#include "REL/IHook.hpp"
#include "REL/Iddb.hpp"
#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REL/Trampoline.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Formatting.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Logging/ISink.hpp"
#include "REX/Logging/Level.hpp"
#include "REX/Logging/Sinks/RotatingFileSink.hpp"
#include "REX/Logging/Sinks/WindowsDebugSink.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"
#include "REX/Singleton.hpp"
#include "REX/System.hpp"
#include "REX/Version.hpp"
#include "REX/W32/SHELL32.hpp"

namespace F4SE::Impl
{
	namespace
	{
		template <class T>
		class EventFunctorList final
		{
		public:
			using value_type = std::decay_t<T>;

			static_assert(std::is_function_v<std::remove_pointer_t<T>>);

			EventFunctorList() = default;
			~EventFunctorList() noexcept = default;

			EventFunctorList(const EventFunctorList&) = delete;
			EventFunctorList(EventFunctorList&&) = delete;

			auto operator=(const EventFunctorList&) -> EventFunctorList& = delete;
			auto operator=(EventFunctorList&&) -> EventFunctorList& = delete;

			template <class... Args>
			void Register(REX::NotNull<std::move_only_function<value_type>> a_callback, Args&&... a_args)
				requires(requires { std::invoke(a_callback.get(), std::forward<Args>(a_args)...); })
			{
				const auto callbackLock = std::scoped_lock(_callbackMutex);

				if (_ran) {
					std::invoke(a_callback.get(), std::forward<Args>(a_args)...);
					return;
				}

				_callbacks.push_back(std::move(a_callback));
			}

			template <class... Args>
			auto Run(Args&&... a_args) -> bool
				requires(requires {
					std::invoke(
						std::declval<REX::NotNull<std::move_only_function<value_type>>>().get(),
						std::forward<Args>(a_args)...);
				})
			{
				const auto callbackLock = std::scoped_lock(_callbackMutex);

				if (_ran) {
					return false;
				}

				for (const auto& callback : _callbacks) {
					std::invoke(callback.get(), std::forward<Args>(a_args)...);
				}

				_callbacks.clear();
				_callbacks.shrink_to_fit();

				_ran = true;
				return true;
			}

		private:
			mutable std::mutex _callbackMutex;
			std::vector<REX::NotNull<std::move_only_function<value_type>>> _callbacks;
			bool _ran{false};
		};

		class SharedObjectFactoryList final : public F4SE::ISharedObjectFactoryList
		{
		private:
			using super = F4SE::ISharedObjectFactoryList;

		public:
			using super::const_pointer;
			using super::pointer;
			using super::value_type;

			SharedObjectFactoryList() = default;
			~SharedObjectFactoryList() noexcept override = default;

			SharedObjectFactoryList(const SharedObjectFactoryList&) = delete;
			SharedObjectFactoryList(SharedObjectFactoryList&&) = delete;

			auto operator=(const SharedObjectFactoryList&) -> SharedObjectFactoryList& = delete;
			auto operator=(SharedObjectFactoryList&&) -> SharedObjectFactoryList& = delete;

			[[nodiscard]]
			auto GetObject(REX::Observer<const_pointer> a_object) const -> std::shared_ptr<value_type> override
			{
				if (!a_object) {
					return nullptr;
				}

				const auto objectLock = std::shared_lock(_objectMutex);

				const auto objectIt = _objectMap.find(a_object);
				if (objectIt == _objectMap.end()) {
					return nullptr;
				}

				return objectIt->second.get();
			}

			void AddObject(REX::NotNull<std::shared_ptr<value_type>> a_object) override
			{
				const auto objectLock = std::scoped_lock(_objectMutex);
				_objectMap.emplace(a_object.get().get(), a_object);
			}

			auto DeleteObject(REX::Owner<pointer> a_object) noexcept -> bool override
			{
				if (!a_object) {
					return false;
				}

				const auto objectLock = std::scoped_lock(_objectMutex);

				const auto objectIt = _objectMap.find(a_object);
				if (objectIt == _objectMap.end()) {
					return false;
				}

				_objectMap.erase(objectIt);
				return true;
			}

		private:
			mutable std::shared_mutex _objectMutex;
			std::unordered_map<REX::Observer<const_pointer>, REX::NotNull<std::shared_ptr<value_type>>> _objectMap;
		};

		class ScriptLogEventSink final : public RE::BSTEventSink<RE::BSScript::LogEvent>
		{
		public:
			explicit ScriptLogEventSink(REX::NotNull<std::shared_ptr<REX::Logging::ILogger>> a_logger) noexcept :
				_logger(std::move(a_logger))
			{
			}

			~ScriptLogEventSink() noexcept override = default;

			ScriptLogEventSink(const ScriptLogEventSink&) = delete;
			ScriptLogEventSink(ScriptLogEventSink&&) = delete;

			auto operator=(const ScriptLogEventSink&) -> ScriptLogEventSink& = delete;
			auto operator=(ScriptLogEventSink&&) -> ScriptLogEventSink& = delete;

			auto ProcessEvent(
				const RE::BSScript::LogEvent& a_event,
				[[maybe_unused]] RE::BSTEventSource<RE::BSScript::LogEvent>* a_eventSource)
				-> RE::BSEventNotifyControl override
			{
				const auto* logMessageFunctor =
					dynamic_cast<const RE::BSScript::StackErrorMessage*>(a_event.errorMessage);
				if (!logMessageFunctor) {
					return RE::BSEventNotifyControl::Continue;
				}

				const auto logMessage = logMessageFunctor->GetMessage();
				const auto logLevel = GetLogLevelForScriptSeverity(a_event.severity.get());
				const auto stackID = logMessageFunctor->GetStackID();

				_logger->Log(logLevel, "[Papyrus] [Stack ID: {}] {}"sv, stackID, logMessage);

				return RE::BSEventNotifyControl::Continue;
			}

		private:
			[[nodiscard]]
			static constexpr auto GetLogLevelForScriptSeverity(RE::BSScript::LogSeverity a_logLevel) noexcept
				-> REX::Logging::Level
			{
				switch (a_logLevel) {
					case RE::BSScript::LogSeverity::Info: {
						return REX::Logging::Level::Information;
					}
					case RE::BSScript::LogSeverity::Warning: {
						return REX::Logging::Level::Warning;
					}
					case RE::BSScript::LogSeverity::Error: {
						return REX::Logging::Level::Error;
					}
					case RE::BSScript::LogSeverity::Fatal: {
						return REX::Logging::Level::Critical;
					}
					[[unlikely]]
					default: {
						REX::Assert(false);
						return REX::Logging::Level::None;
					}
				}
			}

			REX::NotNull<std::shared_ptr<REX::Logging::ILogger>> _logger;
		};

		class MenuInfoMap final : public F4SE::Menus::IMenuInfoMap
		{
		public:
			MenuInfoMap() = default;
			~MenuInfoMap() noexcept override = default;

			MenuInfoMap(const MenuInfoMap&) = delete;
			MenuInfoMap(MenuInfoMap&&) = delete;

			auto operator=(const MenuInfoMap&) -> MenuInfoMap& = delete;
			auto operator=(MenuInfoMap&&) -> MenuInfoMap& = delete;

			[[nodiscard]]
			auto Contains(const RE::BSFixedString& a_menuName) const noexcept -> bool override
			{
				const auto menuLock = std::shared_lock(_menuMutex);
				return _menuMap.contains(a_menuName);
			}

			[[nodiscard]]
			auto GetValue(const RE::BSFixedString& a_menuName) const noexcept
				-> std::shared_ptr<F4SE::Menus::MenuInfo> override
			{
				const auto menuLock = std::shared_lock(_menuMutex);

				const auto menuIt = _menuMap.find(a_menuName);
				if (menuIt == _menuMap.end()) {
					return nullptr;
				}

				return menuIt->second.get();
			}

			auto Add(REX::NotNull<std::shared_ptr<F4SE::Menus::MenuInfo>> a_menu) -> bool override
			{
				const auto menuLock = std::scoped_lock(_menuMutex);
				const auto&& [_, inserted] = _menuMap.emplace(a_menu->GetMenuName(), std::move(a_menu));
				return inserted;
			}

			auto Remove(const RE::BSFixedString& a_menuName) noexcept -> bool override
			{
				const auto menuLock = std::scoped_lock(_menuMutex);

				const auto menuIt = _menuMap.find(a_menuName);
				if (menuIt == _menuMap.end()) {
					return false;
				}

				_menuMap.erase(menuIt);
				return true;
			}

			void Clear() noexcept override
			{
				const auto menuLock = std::scoped_lock(_menuMutex);
				_menuMap.clear();
			}

		private:
			mutable std::shared_mutex _menuMutex;
			std::unordered_map<RE::BSFixedString, REX::NotNull<std::shared_ptr<F4SE::Menus::MenuInfo>>> _menuMap;
		};

		class MenuAssetLoaderMap final : public F4SE::Menus::IMenuAssetLoaderMap
		{
		public:
			MenuAssetLoaderMap() = default;
			~MenuAssetLoaderMap() noexcept override = default;

			MenuAssetLoaderMap(const MenuAssetLoaderMap&) = delete;
			MenuAssetLoaderMap(MenuAssetLoaderMap&&) = delete;

			auto operator=(const MenuAssetLoaderMap&) -> MenuAssetLoaderMap& = delete;
			auto operator=(MenuAssetLoaderMap&&) -> MenuAssetLoaderMap& = delete;

			[[nodiscard]]
			auto Contains(const RE::BSFixedString& a_menuName) const noexcept -> bool override
			{
				const auto assetLoaderLock = std::shared_lock(_assetLoaderMutex);
				return _assetLoaderMap.contains(a_menuName);
			}

			[[nodiscard]]
			auto Contains(REX::NotNull<std::shared_ptr<F4SE::Menus::MenuAssetLoader>> a_assetLoader) const noexcept
				-> bool override
			{
				const auto assetLoaderLock = std::shared_lock(_assetLoaderMutex);

				const auto menuName = RE::BSFixedString(a_assetLoader->GetMenuAssetInfo()->GetMenuName());
				const auto assetRange = _assetLoaderMap.equal_range(menuName);

				for (auto assetIt = assetRange.first; assetIt != assetRange.second; assetIt++) {
					if (assetIt->second == a_assetLoader) {
						return true;
					}
				}

				return false;
			}

			void Add(REX::NotNull<std::shared_ptr<F4SE::Menus::MenuAssetLoader>> a_assetLoader) override
			{
				const auto assetLoaderLock = std::scoped_lock(_assetLoaderMutex);
				_assetLoaderMap.emplace(a_assetLoader->GetMenuAssetInfo()->GetMenuName(), std::move(a_assetLoader));
			}

			auto Remove(const RE::BSFixedString& a_menuName) noexcept -> std::size_t override
			{
				const auto assetLoaderLock = std::scoped_lock(_assetLoaderMutex);
				return _assetLoaderMap.erase(a_menuName);
			}

			auto Remove(const REX::NotNull<std::shared_ptr<F4SE::Menus::MenuAssetLoader>>& a_assetLoader) noexcept
				-> bool override
			{
				const auto assetLoaderLock = std::scoped_lock(_assetLoaderMutex);

				const auto menuName = RE::BSFixedString(a_assetLoader->GetMenuAssetInfo()->GetMenuName());
				const auto assetRange = _assetLoaderMap.equal_range(menuName);

				for (auto assetIt = assetRange.first; assetIt != assetRange.second; assetIt++) {
					if (assetIt->second == a_assetLoader) {
						_assetLoaderMap.erase(assetIt);
						return true;
					}
				}

				return false;
			}

			void Clear() noexcept override
			{
				const auto assetLoaderLock = std::scoped_lock(_assetLoaderMutex);
				_assetLoaderMap.clear();
			}

		private:
			mutable std::shared_mutex _assetLoaderMutex;
			std::unordered_multimap<RE::BSFixedString, REX::NotNull<std::shared_ptr<F4SE::Menus::MenuAssetLoader>>>
				_assetLoaderMap;
		};

		[[nodiscard]]
		auto CreateTranslator() -> std::optional<F4SE::Translator>
		{
			const auto* scaleformManager = RE::BSScaleformManager::GetSingleton();
			if (!scaleformManager) {
				return std::nullopt;
			}

			auto scaleformTranslator = scaleformManager->GetTranslator();
			if (!scaleformTranslator) {
				return std::nullopt;
			}

			auto languageCode = RE::BSScaleformTranslator::GetLanguage();
			if (languageCode.empty()) {
				return std::nullopt;
			}

			return F4SE::Translator(std::move(languageCode), std::move(scaleformTranslator));
		}

		class Api final : public REX::Singleton<Api>
		{
		public:
			Api() = default;
			~Api() noexcept = default;

			Api(const Api&) = delete;
			Api(Api&&) = delete;

			auto operator=(const Api&) -> Api& = delete;
			auto operator=(Api&&) -> Api& = delete;

			[[nodiscard]]
			static auto GetLogFilePath(std::string_view a_saveFolderName, std::string_view a_logBaseName) noexcept
				-> std::expected<std::filesystem::path, REX::SystemError>;

			[[nodiscard]]
			auto GetOrCreateTranslator() -> std::optional<F4SE::Translator>;

			void Setup(REX::NotNull<const F4SE::PreLoadInterface*> a_interface, SetupOptions a_info);
			void Setup(REX::NotNull<const F4SE::LoadInterface*> a_interface, SetupOptions a_info);

		private:
			void SetupImpl(REX::NotNull<const F4SE::QueryInterface*> a_interface, SetupOptions a_info);
			void SetupRuntime(REX::Version a_runtimeVersion);
			void SetupLogger();
			void SetupModule();
			void SetupIddb();
			void SetupTrampoline();
			void SetupHooks(REL::HookStep a_step);

		public:
			SetupOptions setupOptions;
			F4SE::PluginHandle pluginHandle{F4SE::INVALID_PLUGIN_HANDLE};
			std::string_view pluginName;
			std::string_view pluginAuthor;
			REX::Version pluginVersion;
			F4SE::QueryInterface::PluginInfoFunctor pluginInfoFunctor{nullptr};
			std::uint32_t releaseIndex{0};
			REX::Version xseVersion;
			REX::Version runtimeVersion;
			std::string_view saveFolderName;

			const F4SE::MessagingInterface* messagingInterface{nullptr};
			const F4SE::ScaleformInterface* scaleformInterface{nullptr};
			const F4SE::PapyrusInterface* papyrusInterface{nullptr};
			const F4SE::SerializationInterface* serializationInterface{nullptr};
			const F4SE::TaskInterface* taskInterface{nullptr};
			const F4SE::ObjectInterface* objectInterface{nullptr};
			const F4SE::DelayFunctorManager* delayFunctorManager{nullptr};
			const F4SE::ObjectRegistry* objectRegistry{nullptr};
			const F4SE::PersistentObjectStorage* persistentObjectStorage{nullptr};
			const F4SE::TrampolineInterface* trampolineInterface{nullptr};

			std::array<EventFunctorList<ApiLoadCallback>, std::to_underlying(REL::HookStep::_Count)> eventFunctors;

			std::shared_ptr<REL::Trampoline> trampoline;
			std::shared_ptr<REL::HookList> hookList;
			std::shared_ptr<SharedObjectFactoryList> sharedObjectFactoryStore;
			std::shared_ptr<ScriptLogEventSink> scriptLogEventSink;
			std::shared_ptr<MenuInfoMap> menuInfoMap;
			std::shared_ptr<MenuAssetLoaderMap> menuAssetLoaderMap;
			std::optional<F4SE::Translator> translator;

			mutable std::once_flag preLoadOnceFlag;
			mutable std::once_flag loadOnceFlag;
			mutable std::once_flag initOnceFlag;
			mutable std::once_flag initModuleOnceFlag;
			mutable std::once_flag initIddbOnceFlag;
			mutable std::once_flag initLoggerOnceFlag;
			mutable std::once_flag initTrampolineOnceFlag;
			mutable std::once_flag initHooksOnceFlag;
		};

		auto Api::GetLogFilePath(std::string_view a_saveFolderName, std::string_view a_logBaseName) noexcept
			-> std::expected<std::filesystem::path, REX::SystemError>
		{
			const auto userDocumentsPath =
				REX::GetKnownFolderPath(REX::W32::FOLDERID_Documents, REX::W32::KF_FLAG_DEFAULT);
			if (!userDocumentsPath.has_value()) [[unlikely]] {
				return std::unexpected(userDocumentsPath.error());
			}

			try {
				return std::filesystem::path(
					REX::Format(
						"{}/My Games/{}/F4SE/{}.log"sv,
						userDocumentsPath->generic_string(),
						a_saveFolderName,
						a_logBaseName),
					std::filesystem::path::generic_format);
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}
		}
	}

	auto Api::GetOrCreateTranslator() -> std::optional<F4SE::Translator>
	{
		if (translator.has_value()) {
			return translator;
		}

		auto newTranslator = CreateTranslator();
		if (!newTranslator.has_value()) {
			return std::nullopt;
		}

		translator = std::move(newTranslator).value();
		return translator;
	}

	void Api::Setup(REX::NotNull<const F4SE::PreLoadInterface*> a_interface, SetupOptions a_info)
	{
		std::call_once(preLoadOnceFlag, [this, a_interface, &a_info]() -> void {
			SetupImpl(a_interface, std::move(a_info));

			trampolineInterface = a_interface->QueryOrFail<F4SE::TrampolineInterface>().get();

			constexpr auto HOOK_STEP = REL::HookStep::PreLoad;

			const auto logger = setupOptions.logger;
			if (logger) {
				logger->LogDebug("{}"sv, HOOK_STEP);
			}

			eventFunctors[std::to_underlying(HOOK_STEP) - 1].Run(hookList);

			SetupTrampoline();
			SetupHooks(HOOK_STEP);
		});
	}

	void Api::Setup(REX::NotNull<const F4SE::LoadInterface*> a_interface, SetupOptions a_info)
	{
		std::call_once(loadOnceFlag, [this, a_interface, &a_info]() -> void {
			SetupImpl(a_interface, std::move(a_info));

			messagingInterface = a_interface->QueryOrFail<F4SE::MessagingInterface>().get();
			scaleformInterface = a_interface->QueryOrFail<F4SE::ScaleformInterface>().get();
			papyrusInterface = a_interface->QueryOrFail<F4SE::PapyrusInterface>().get();
			serializationInterface = a_interface->QueryOrFail<F4SE::SerializationInterface>().get();
			taskInterface = a_interface->QueryOrFail<F4SE::TaskInterface>().get();
			trampolineInterface = a_interface->QueryOrFail<F4SE::TrampolineInterface>().get();
			objectInterface = a_interface->QueryOrFail<F4SE::ObjectInterface>().get();
			delayFunctorManager = std::addressof(objectInterface->GetDelayFunctorManager());
			objectRegistry = std::addressof(objectInterface->GetObjectRegistry());
			persistentObjectStorage = std::addressof(objectInterface->GetPersistentObjectStorage());

			constexpr auto HOOK_STEP = REL::HookStep::Load;

			const auto logger = setupOptions.logger;
			if (logger) {
				logger->LogDebug("{}"sv, HOOK_STEP);
			}

			eventFunctors[std::to_underlying(HOOK_STEP) - 1].Run(hookList);

			SetupTrampoline();
			SetupHooks(HOOK_STEP);
		});
	}

	void Api::SetupImpl(REX::NotNull<const F4SE::QueryInterface*> a_interface, SetupOptions a_info)
	{
		setupOptions = std::move(a_info);

		std::call_once(initOnceFlag, [this, a_interface]() -> void {
			const auto& pluginData = F4SE::PluginVersionData::GetSingleton();

			pluginName = pluginData.GetPluginName();
			pluginAuthor = pluginData.GetPluginAuthor();
			pluginVersion = pluginData.GetPluginVersion();

			runtimeVersion = a_interface->GetRuntimeVersion();
			SetupRuntime(runtimeVersion);

			pluginHandle = a_interface->GetPluginHandle();
			pluginInfoFunctor = a_interface->GetPluginInfoFunctor();
			releaseIndex = a_interface->GetReleaseIndex();
			xseVersion = a_interface->GetXseVersion();
			saveFolderName = a_interface->GetSaveFolderName();

			trampoline = std::make_shared<REL::Trampoline>(setupOptions.logger);
			hookList = std::make_shared<REL::HookList>(setupOptions.logger);
			sharedObjectFactoryStore = std::make_shared<SharedObjectFactoryList>();
			scriptLogEventSink = std::make_shared<ScriptLogEventSink>(setupOptions.logger);
			menuInfoMap = std::make_shared<MenuInfoMap>();
			menuAssetLoaderMap = std::make_shared<MenuAssetLoaderMap>();

			SetupLogger();
			SetupModule();
			SetupIddb();

			const auto logger = setupOptions.logger;
			if (logger) {
				logger->LogInformation(
					"Setup; Plugin: v{}, Runtime: v{}, XSE: v{}"sv,
					pluginVersion,
					runtimeVersion,
					xseVersion);
			}
		});
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void Api::SetupRuntime(REX::Version a_runtimeVersion)
	{
		static_assert(F4SE::RUNTIME_LATEST_VR < F4SE::RUNTIME_LATEST_OG);
		static_assert(F4SE::RUNTIME_LATEST_OG < F4SE::RUNTIME_LATEST_NG);
		static_assert(F4SE::RUNTIME_LATEST_NG < F4SE::RUNTIME_LATEST_AE);

		auto runtime = std::optional<REL::Runtime>();

#if (COMMONLIB_RUNTIME_VR == 1)
		if (a_runtimeVersion == F4SE::RUNTIME_LATEST_VR.GetMinVersion()) {
			runtime = REL::CreateRuntimeVR(a_runtimeVersion);
		}
#endif

#if (COMMONLIB_RUNTIME_OG == 1)
		if (a_runtimeVersion == F4SE::RUNTIME_LATEST_OG.GetMinVersion()) {
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

#if (COMMONLIB_RUNTIME_NG == 1)
		if (a_runtimeVersion == F4SE::RUNTIME_LATEST_NG.GetMinVersion()) {
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

#if (COMMONLIB_RUNTIME_AE == 1 || (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0))
		if (a_runtimeVersion >= F4SE::RUNTIME_LATEST_AE.GetMinVersion()) {
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

		if (!runtime.has_value()) [[unlikely]] {
			REX::Fail(
				"Failed to initialize the runtime.\n"
				"The version is unsupported.\n"
				"Runtime Version: {}"sv,
				a_runtimeVersion);
		}

		REL::Module::GetSingleton().SetRuntime(runtime.value());
	}

	void Api::SetupModule()
	{
		std::call_once(initModuleOnceFlag, []() -> void {
			REL::Module::GetSingleton().Setup();
		});
	}

	void Api::SetupIddb()
	{
		std::call_once(initIddbOnceFlag, []() -> void {
			REL::Iddb::GetSingleton().Setup();
		});
	}

	void Api::SetupLogger()
	{
		const auto logger = setupOptions.logger;
		if (!logger || logger->GetMinLevel() == REX::Logging::Level::None) {
			return;
		}

		std::call_once(initLoggerOnceFlag, [this, logger]() -> void {
			const auto& pluginData = F4SE::PluginVersionData::GetSingleton();

			auto logFilePath = GetLogFilePath(saveFolderName, pluginData.GetPluginName());
			if (!logFilePath.has_value()) [[unlikely]] {
				logger->LogError(
					"Failed to get the log directory.\n"
					"System Error (0x{:08X}): {}"sv,
					logFilePath.error().value(),
					logFilePath.error().message());
				return;
			}

			const auto logSinks = std::initializer_list<REX::NotNull<std::shared_ptr<REX::Logging::ISink>>>{
				std::make_shared<REX::Logging::Sinks::WindowsDebugSink>(),
				std::make_shared<REX::Logging::Sinks::RotatingFileSink>(
					std::move(logFilePath).value(),
					setupOptions.logRotationCount,
					setupOptions.logRotationByteSize)
			};

			logger->AddSinkRange(logSinks);
		});
	}

	void Api::SetupTrampoline()
	{
		if (!setupOptions.useTrampoline) {
			return;
		}

		std::call_once(initTrampolineOnceFlag, [this]() -> void {
			auto trampolineSize = setupOptions.trampolineSize;
			if (trampolineSize == 0) {
				trampolineSize = hookList->GetTrampolineSize();
			}

			auto* mem = trampolineInterface->AllocateFromBranchPool(trampolineSize);
			if (!mem) {
				trampoline->Create(trampolineSize);
				return;
			}

			trampoline->Setup(mem, trampolineSize);
		});
	}

	void Api::SetupHooks(REL::HookStep a_step)
	{
		if (!setupOptions.useHooks) {
			return;
		}

		std::call_once(initHooksOnceFlag, [this, a_step]() -> void {
			hookList->Setup(*trampoline);
			hookList->Enable(a_step);
		});
	}
}

namespace F4SE
{
	void Setup(REX::NotNull<REX::Observer<const PreLoadInterface*>> a_interface, SetupOptions a_info)
	{
		Impl::Api::GetSingleton().Setup(a_interface, std::move(a_info));
	}

	void Setup(REX::NotNull<REX::Observer<const LoadInterface*>> a_interface, SetupOptions a_info)
	{
		Impl::Api::GetSingleton().Setup(a_interface, std::move(a_info));
	}

	void RegisterForOnPreLoad(REX::NotNull<std::move_only_function<ApiLoadCallback>> a_callback)
	{
		auto& api = Impl::Api::GetSingleton();
		api.eventFunctors[std::to_underlying(REL::HookStep::PreLoad) - 1].Register(std::move(a_callback), api.hookList);
	}

	void RegisterForOnLoad(REX::NotNull<std::move_only_function<ApiLoadCallback>> a_callback)
	{
		auto& api = Impl::Api::GetSingleton();
		api.eventFunctors[std::to_underlying(REL::HookStep::Load) - 1].Register(std::move(a_callback), api.hookList);
	}

	auto GetSetupOptions() noexcept -> const SetupOptions&
	{
		return Impl::Api::GetSingleton().setupOptions;
	}

	auto GetPluginHandle() noexcept -> PluginHandle
	{
		return Impl::Api::GetSingleton().pluginHandle;
	}

	auto GetPluginName() noexcept -> std::string_view
	{
		return Impl::Api::GetSingleton().pluginName;
	}

	auto GetPluginAuthor() noexcept -> std::string_view
	{
		return Impl::Api::GetSingleton().pluginAuthor;
	}

	auto GetPluginVersion() noexcept -> REX::Version
	{
		return Impl::Api::GetSingleton().pluginVersion;
	}

	auto GetPluginInfo(const char* a_name) noexcept -> REX::Observer<const PluginInfo*>
	{
		auto* pluginInfoFunctor = Impl::Api::GetSingleton().pluginInfoFunctor;
		return pluginInfoFunctor ? std::invoke(pluginInfoFunctor, a_name) : nullptr;
	}

	auto GetReleaseIndex() noexcept -> std::uint32_t
	{
		return Impl::Api::GetSingleton().releaseIndex;
	}

	auto GetXseVersion() noexcept -> REX::Version
	{
		return Impl::Api::GetSingleton().xseVersion;
	}

	auto GetRuntimeVersion() noexcept -> REX::Version
	{
		return Impl::Api::GetSingleton().runtimeVersion;
	}

	auto GetSaveFolderName() noexcept -> std::string_view
	{
		return Impl::Api::GetSingleton().saveFolderName;
	}

	auto GetMessagingInterface() noexcept -> REX::NotNull<REX::Observer<const MessagingInterface*>>
	{
		return Impl::Api::GetSingleton().messagingInterface;
	}

	auto GetScaleformInterface() noexcept -> REX::NotNull<REX::Observer<const ScaleformInterface*>>
	{
		return Impl::Api::GetSingleton().scaleformInterface;
	}

	auto GetPapyrusInterface() noexcept -> REX::NotNull<REX::Observer<const PapyrusInterface*>>
	{
		return Impl::Api::GetSingleton().papyrusInterface;
	}

	auto GetSerializationInterface() noexcept -> REX::NotNull<REX::Observer<const SerializationInterface*>>
	{
		return Impl::Api::GetSingleton().serializationInterface;
	}

	auto GetTaskInterface() noexcept -> REX::NotNull<REX::Observer<const TaskInterface*>>
	{
		return Impl::Api::GetSingleton().taskInterface;
	}

	auto GetObjectInterface() noexcept -> REX::NotNull<REX::Observer<const ObjectInterface*>>
	{
		return Impl::Api::GetSingleton().objectInterface;
	}

	auto GetDelayFunctorManager() noexcept -> REX::NotNull<REX::Observer<const DelayFunctorManager*>>
	{
		return Impl::Api::GetSingleton().delayFunctorManager;
	}

	auto GetObjectRegistry() noexcept -> REX::NotNull<REX::Observer<const ObjectRegistry*>>
	{
		return Impl::Api::GetSingleton().objectRegistry;
	}

	auto GetPersistentObjectStorage() noexcept -> REX::NotNull<REX::Observer<const PersistentObjectStorage*>>
	{
		return Impl::Api::GetSingleton().persistentObjectStorage;
	}

	auto GetTrampolineInterface() noexcept -> REX::NotNull<REX::Observer<const TrampolineInterface*>>
	{
		return Impl::Api::GetSingleton().trampolineInterface;
	}

	auto GetTrampoline() noexcept -> REX::NotNull<std::shared_ptr<REL::Trampoline>>
	{
		return Impl::Api::GetSingleton().trampoline;
	}

	auto GetHookList() noexcept -> REX::NotNull<std::shared_ptr<REL::HookList>>
	{
		return Impl::Api::GetSingleton().hookList;
	}

	auto GetSharedObjectFactoryList() noexcept -> REX::NotNull<std::shared_ptr<F4SE::ISharedObjectFactoryList>>
	{
		return Impl::Api::GetSingleton().sharedObjectFactoryStore;
	}

	auto GetScriptLogEventSink() noexcept -> REX::NotNull<std::shared_ptr<RE::BSTEventSink<RE::BSScript::LogEvent>>>
	{
		return Impl::Api::GetSingleton().scriptLogEventSink;
	}

	auto GetMenuInfoMap() noexcept -> REX::NotNull<std::shared_ptr<F4SE::Menus::IMenuInfoMap>>
	{
		return Impl::Api::GetSingleton().menuInfoMap;
	}

	auto GetMenuAssetLoaderMap() noexcept -> REX::NotNull<std::shared_ptr<F4SE::Menus::IMenuAssetLoaderMap>>
	{
		return Impl::Api::GetSingleton().menuAssetLoaderMap;
	}

	auto GetOrCreateTranslator() -> std::optional<F4SE::Translator>
	{
		return Impl::Api::GetSingleton().GetOrCreateTranslator();
	}
}

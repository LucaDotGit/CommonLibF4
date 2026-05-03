#include "F4SE/API.hpp"

#include "F4SE/DelayFunctorManager.hpp"
#include "F4SE/LoadInterface.hpp"
#include "F4SE/MessagingInterface.hpp"
#include "F4SE/ObjectInterface.hpp"
#include "F4SE/ObjectRegistry.hpp"
#include "F4SE/PapyrusInterface.hpp"
#include "F4SE/PersistentObjectStorage.hpp"
#include "F4SE/PluginInfo.hpp"
#include "F4SE/PluginVersionData.hpp"
#include "F4SE/PreLoadInterface.hpp"
#include "F4SE/QueryInterface.hpp"
#include "F4SE/Runtimes.hpp"
#include "F4SE/ScaleformInterface.hpp"
#include "F4SE/SerializationInterface.hpp"
#include "F4SE/TaskInterface.hpp"
#include "F4SE/TrampolineInterface.hpp"

#include "REL/HookStore.hpp"
#include "REL/IHook.hpp"
#include "REL/Iddb.hpp"
#include "REL/Module.hpp"
#include "REL/Trampoline.hpp"

#include "REX/Contract.hpp"
#include "REX/ErrorCode.hpp"
#include "REX/Format.hpp"
#include "REX/Log.hpp"
#include "REX/Message.hpp"
#include "REX/Singleton.hpp"
#include "REX/W32/OLE32.hpp"
#include "REX/W32/SHELL32.hpp"

namespace F4SE::Impl
{
	class CallbackEvent final
	{
	public:
		using value_type = REX::NotNull<std::function<void()>>;

		CallbackEvent() = default;
		~CallbackEvent() noexcept = default;

		CallbackEvent(const CallbackEvent&) = delete;
		CallbackEvent(CallbackEvent&&) = delete;

		CallbackEvent& operator=(const CallbackEvent&) = delete;
		CallbackEvent& operator=(CallbackEvent&&) = delete;

		bool Register(value_type a_callback)
		{
			const auto callbackLock = std::scoped_lock(_mutex);

			if (_ran) {
				std::invoke(*a_callback);
				return true;
			}

			_callbacks.push_back(std::move(a_callback));
			return true;
		}

		bool Run()
		{
			const auto callbackLock = std::scoped_lock(_mutex);

			if (_ran) {
				return false;
			}

			for (const auto& callback : _callbacks) {
				std::invoke(*callback);
			}

			_callbacks.clear();
			_callbacks.shrink_to_fit();

			_ran = true;
			return true;
		}

		void Clear() noexcept
		{
			const auto callbackLock = std::scoped_lock(_mutex);

			_callbacks.clear();
			_callbacks.shrink_to_fit();
		}

		void Dispose() noexcept
		{
			const auto callbackLock = std::scoped_lock(_mutex);

			_callbacks.clear();
			_callbacks.shrink_to_fit();

			_ran = false;
		}

	private:
		mutable std::mutex _mutex;
		std::vector<value_type> _callbacks;
		bool _ran{ false };
	};

	class API final
		: public REX::Singleton<API>
	{
	public:
		API() = default;
		~API() noexcept = default;

		API(const API&) = delete;
		API(API&&) = delete;

		API& operator=(const API&) = delete;
		API& operator=(API&&) = delete;

		[[nodiscard]] static auto GetLogDirectoryPath(std::string_view a_saveFolderName) -> std::expected<std::filesystem::path, REX::SystemError>;

		void Init(REX::NotNull<const F4SE::PreLoadInterface*> a_interface, const InitInfo& a_info);
		void Init(REX::NotNull<const F4SE::LoadInterface*> a_interface, const InitInfo& a_info);

	private:
		void InitImpl(REX::NotNull<const F4SE::QueryInterface*> a_interface, const InitInfo& a_info);
		void InitLogger();
		void InitModule() const;
		void InitIddb() const;
		void InitTrampoline();
		void InitHooks(REL::HookStep a_step) const;

	public:
		InitInfo info;
		F4SE::PluginHandle pluginHandle{ INVALID_PLUGIN_HANDLE };
		std::string_view pluginName;
		std::string_view pluginAuthor;
		REX::Version pluginVersion;
		F4SE::QueryInterface::PluginInfoAccessor pluginInfoAccessor{ nullptr };
		std::uint32_t releaseIndex{ 0 };
		REX::Version f4seVersion;
		REX::Version runtimeVersion;
		std::string_view saveFolderName;
		std::filesystem::path logDirectoryPath;

		const F4SE::MessagingInterface* messagingInterface{ nullptr };
		const F4SE::ScaleformInterface* scaleformInterface{ nullptr };
		const F4SE::PapyrusInterface* papyrusInterface{ nullptr };
		const F4SE::SerializationInterface* serializationInterface{ nullptr };
		const F4SE::TaskInterface* taskInterface{ nullptr };
		const F4SE::ObjectInterface* objectInterface{ nullptr };
		const F4SE::DelayFunctorManager* delayFunctorManager{ nullptr };
		const F4SE::ObjectRegistry* objectRegistry{ nullptr };
		const F4SE::PersistentObjectStorage* persistentObjectStorage{ nullptr };
		const F4SE::TrampolineInterface* trampolineInterface{ nullptr };

		CallbackEvent onPreLoadEvent;
		CallbackEvent onLoadEvent;
	};

	auto API::GetLogDirectoryPath(std::string_view a_saveFolderName) -> std::expected<std::filesystem::path, REX::SystemError>
	{
		auto* knownToken = static_cast<void*>(nullptr);
		auto* knownBuffer = static_cast<wchar_t*>(nullptr);

		if (REX::W32::SHGetKnownFolderPath(REX::W32::FOLDERID_Documents, REX::W32::KF_FLAG_DEFAULT, knownToken, std::addressof(knownBuffer)) != 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto knownPath = std::unique_ptr<wchar_t, decltype(&REX::W32::CoTaskMemFree)>(knownBuffer, REX::W32::CoTaskMemFree);
		if (!knownPath) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto path = std::filesystem::path(knownPath.get(), std::filesystem::path::generic_format);
		path /= REX::Format("My Games/{}/F4SE"sv, a_saveFolderName);
		return path;
	}

	void API::InitImpl(REX::NotNull<const F4SE::QueryInterface*> a_interface, const InitInfo& a_info)
	{
		this->info = a_info;

		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, [this, a_interface]() {
			const auto pluginInfo = F4SE::PluginVersionData::GetSingleton();

			this->pluginName = pluginInfo->GetPluginName();
			this->pluginAuthor = pluginInfo->GetPluginName();
			this->pluginVersion = pluginInfo->GetPluginVersion();

			this->runtimeVersion = a_interface->GetRuntimeVersion();
			F4SE::Impl::InitRuntime(this->runtimeVersion);

			this->pluginHandle = a_interface->GetPluginHandle();
			this->pluginInfoAccessor = a_interface->GetPluginInfoAccessor();
			this->releaseIndex = a_interface->GetReleaseIndex();
			this->f4seVersion = a_interface->GetF4SEVersion();
			this->saveFolderName = a_interface->GetSaveFolderName();

			InitLogger();
			InitModule();
			InitIddb();
		});
	}

	void API::Init(REX::NotNull<const F4SE::PreLoadInterface*> a_interface, const InitInfo& a_info)
	{
		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, [this, a_interface, &a_info]() {
			InitImpl(a_interface, a_info);

			this->trampolineInterface = a_interface->DoQueryInterface<F4SE::TrampolineInterface>();

			this->onPreLoadEvent.Run();
			this->onPreLoadEvent.Clear();

			InitTrampoline();
			InitHooks(REL::HookStep::kPreLoad);
		});
	}

	void API::Init(REX::NotNull<const F4SE::LoadInterface*> a_interface, const InitInfo& a_info)
	{
		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, [this, a_interface, &a_info]() {
			InitImpl(a_interface, a_info);

			this->messagingInterface = a_interface->DoQueryInterface<F4SE::MessagingInterface>();
			this->scaleformInterface = a_interface->DoQueryInterface<F4SE::ScaleformInterface>();
			this->papyrusInterface = a_interface->DoQueryInterface<F4SE::PapyrusInterface>();
			this->serializationInterface = a_interface->DoQueryInterface<F4SE::SerializationInterface>();
			this->taskInterface = a_interface->DoQueryInterface<F4SE::TaskInterface>();
			this->trampolineInterface = a_interface->DoQueryInterface<F4SE::TrampolineInterface>();
			this->objectInterface = a_interface->DoQueryInterface<F4SE::ObjectInterface>();
			this->delayFunctorManager = std::addressof(objectInterface->GetDelayFunctorManager());
			this->objectRegistry = std::addressof(objectInterface->GetObjectRegistry());
			this->persistentObjectStorage = std::addressof(objectInterface->GetPersistentObjectStorage());

			this->onLoadEvent.Run();
			this->onLoadEvent.Clear();

			InitTrampoline();
			InitHooks(REL::HookStep::kLoad);
		});
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void API::InitModule() const
	{
		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, []() {
			const auto& module = REL::Module::GetSingleton();
			module->Init();
		});
	}

	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	void API::InitIddb() const
	{
		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, []() {
			const auto& iddb = REL::Iddb::GetSingleton();
			iddb->Init();
		});
	}

	void API::InitLogger()
	{
		if (this->info.logLevel == REX::LogLevel::kNone) {
			return;
		}

		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, [this]() {
			auto logDirectoryPath = GetLogDirectoryPath(saveFolderName);
			if (!logDirectoryPath) [[unlikely]] {
				const auto& ioError = logDirectoryPath.error();
				REX::Fail(
					"Failed to get the log directory.\n"
					"System Error (0x{:08X}): {}"sv,
					ioError.value(), ioError.message());
			}

			const auto versionData = F4SE::PluginVersionData::GetSingleton();
			const auto logName = !this->info.logName.empty() ? this->info.logName : REX::DEFAULT_LOGGER_NAME;
			const auto logFileName = !this->info.logFileName.empty() ? this->info.logFileName : versionData->GetPluginName();
			const auto logFormat = !this->info.logFormat.empty() ? this->info.logFormat : REX::DEFAULT_LOGGER_FORMAT;

			auto logInitInfo = REX::LogInitInfo{
				.logName = std::string(logName),
				.logDirectoryPath = *logDirectoryPath,
				.logFileName = std::string(logFileName),
				.logFormat = std::string(logFormat),
				.logLevel = this->info.logLevel,
				.logFileCount = this->info.logFileCount
			};

			this->logDirectoryPath = *std::move(logDirectoryPath);

			REX::InitLogger(std::move(logInitInfo));
			REX::LogInformation("{} v{}"sv, versionData->GetPluginName(), versionData->GetPluginVersion());
		});
	}

	void API::InitTrampoline()
	{
		if (!this->info.useTrampoline) {
			return;
		}

		static constinit auto OnceFlag = std::once_flag();
		std::call_once(OnceFlag, [this]() {
			if (this->info.trampolineSize == 0) {
				const auto& hookStore = REL::GetHookStore();
				this->info.trampolineSize += hookStore->GetTrampolineSize();
			}

			if (!this->trampolineInterface) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			const auto& trampoline = REL::GetTrampoline();

			auto* mem = this->trampolineInterface->AllocateFromBranchPool(this->info.trampolineSize);
			if (!mem) {
				trampoline->Create(this->info.trampolineSize);
				return;
			}

			trampoline->Init(mem, this->info.trampolineSize);
		});
	}

	void API::InitHooks(REL::HookStep a_step) const
	{
		if (!this->info.useHooks) {
			return;
		}

		const auto& hookStore = REL::GetHookStore();
		hookStore->Init();
		hookStore->Enable(a_step);
	}
}

namespace F4SE
{
	void Init(REX::NotNull<const PreLoadInterface*> a_interface, const InitInfo& a_info)
	{
		Impl::API::GetSingleton()->Init(a_interface, a_info);
	}

	void Init(REX::NotNull<const LoadInterface*> a_interface, const InitInfo& a_info)
	{
		Impl::API::GetSingleton()->Init(a_interface, a_info);
	}

	bool RegisterForOnPreLoad(REX::NotNull<std::function<void()>> a_callback)
	{
		return Impl::API::GetSingleton()->onPreLoadEvent.Register(std::move(a_callback));
	}

	bool RegisterForOnLoad(REX::NotNull<std::function<void()>> a_callback)
	{
		return Impl::API::GetSingleton()->onLoadEvent.Register(std::move(a_callback));
	}

	const InitInfo& GetInitInfo() noexcept
	{
		return Impl::API::GetSingleton()->info;
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return Impl::API::GetSingleton()->pluginHandle;
	}

	std::string_view GetPluginName() noexcept
	{
		return Impl::API::GetSingleton()->pluginName;
	}

	std::string_view GetPluginAuthor() noexcept
	{
		return Impl::API::GetSingleton()->pluginAuthor;
	}

	REX::Version GetPluginVersion() noexcept
	{
		return Impl::API::GetSingleton()->pluginVersion;
	}

	const PluginInfo* GetPluginInfo(const char* a_name) noexcept
	{
		auto* pluginInfoAccessor = Impl::API::GetSingleton()->pluginInfoAccessor;
		return pluginInfoAccessor ? std::invoke(pluginInfoAccessor, a_name) : nullptr;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return Impl::API::GetSingleton()->releaseIndex;
	}

	REX::Version GetF4SEVersion() noexcept
	{
		return Impl::API::GetSingleton()->f4seVersion;
	}

	REX::Version GetRuntimeVersion() noexcept
	{
		return Impl::API::GetSingleton()->runtimeVersion;
	}

	std::string_view GetSaveFolderName() noexcept
	{
		return Impl::API::GetSingleton()->saveFolderName;
	}

	const std::filesystem::path& GetLogDirectoryPath() noexcept
	{
		return Impl::API::GetSingleton()->logDirectoryPath;
	}

	auto GetMessagingInterface() noexcept -> REX::NotNull<const MessagingInterface*>
	{
		return Impl::API::GetSingleton()->messagingInterface;
	}

	auto GetScaleformInterface() noexcept -> REX::NotNull<const ScaleformInterface*>
	{
		return Impl::API::GetSingleton()->scaleformInterface;
	}

	auto GetPapyrusInterface() noexcept -> REX::NotNull<const PapyrusInterface*>
	{
		return Impl::API::GetSingleton()->papyrusInterface;
	}

	auto GetSerializationInterface() noexcept -> REX::NotNull<const SerializationInterface*>
	{
		return Impl::API::GetSingleton()->serializationInterface;
	}

	auto GetTaskInterface() noexcept -> REX::NotNull<const TaskInterface*>
	{
		return Impl::API::GetSingleton()->taskInterface;
	}

	auto GetObjectInterface() noexcept -> REX::NotNull<const ObjectInterface*>
	{
		return Impl::API::GetSingleton()->objectInterface;
	}

	auto GetDelayFunctorManager() noexcept -> REX::NotNull<const DelayFunctorManager*>
	{
		return Impl::API::GetSingleton()->delayFunctorManager;
	}

	auto GetObjectRegistry() noexcept -> REX::NotNull<const ObjectRegistry*>
	{
		return Impl::API::GetSingleton()->objectRegistry;
	}

	auto GetPersistentObjectStorage() noexcept -> REX::NotNull<const PersistentObjectStorage*>
	{
		return Impl::API::GetSingleton()->persistentObjectStorage;
	}

	auto GetTrampolineInterface() noexcept -> REX::NotNull<const TrampolineInterface*>
	{
		return Impl::API::GetSingleton()->trampolineInterface;
	}
}

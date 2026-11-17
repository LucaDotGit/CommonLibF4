#pragma once

#include "F4SE/Core.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace RE
{
	template <class T>
	class BSTEventSink;
}

namespace RE::BSScript
{
	class LogEvent;
}

namespace REL
{
	class HookList;
	class Trampoline;
}

namespace REX
{
	class Version;
}

namespace REX::Logging
{
	class ILogger;
}

namespace F4SE
{
	class Translator;
}

namespace F4SE::Menus
{
	class IMenuAssetLoaderMap;
	class IMenuInfoMap;
}

namespace F4SE
{
	class DelayFunctorManager;
	class ISharedObjectFactoryList;
	class LoadInterface;
	class MessagingInterface;
	class ObjectInterface;
	class ObjectRegistry;
	class PapyrusInterface;
	class PersistentObjectStorage;
	class PluginInfo;
	class PreLoadInterface;
	class ScaleformInterface;
	class SerializationInterface;
	class TaskInterface;
	class TrampolineInterface;

	using ApiLoadCallback = void(const REX::NotNull<std::shared_ptr<REL::HookList>>& a_hookList) const;

	inline constexpr auto ROOT_DIRECTORY_PATH = "."sv;
	inline constexpr auto DATA_DIRECTORY_PATH = "Data"sv;
	inline constexpr auto PLUGINS_DIRECTORY_PATH = "Data/F4SE/Plugins"sv;

	class SetupOptions final
	{
	public:
		std::shared_ptr<REX::Logging::ILogger> logger{nullptr};
		std::size_t logRotationCount{0};
		std::size_t logRotationByteSize{0};
		bool useHooks{false};
		bool useTrampoline{false};
		std::size_t trampolineSize{0};
	};

	void Setup(REX::NotNull<REX::Observer<const F4SE::PreLoadInterface*>> a_interface, SetupOptions a_info = {});
	void Setup(REX::NotNull<REX::Observer<const F4SE::LoadInterface*>> a_interface, SetupOptions a_info = {});

	void RegisterForOnPreLoad(REX::NotNull<std::move_only_function<ApiLoadCallback>> a_callback);
	void RegisterForOnLoad(REX::NotNull<std::move_only_function<ApiLoadCallback>> a_callback);

	[[nodiscard]]
	auto GetSetupOptions() noexcept -> const SetupOptions&;

	[[nodiscard]]
	auto GetPluginHandle() noexcept -> F4SE::PluginHandle;

	[[nodiscard]]
	auto GetPluginName() noexcept -> std::string_view;

	[[nodiscard]]
	auto GetPluginAuthor() noexcept -> std::string_view;

	[[nodiscard]]
	auto GetPluginVersion() noexcept -> REX::Version;

	[[nodiscard]]
	auto GetPluginInfo(const char* a_name) noexcept -> REX::Observer<const PluginInfo*>;

	[[nodiscard]]
	auto GetReleaseIndex() noexcept -> std::uint32_t;

	[[nodiscard]]
	auto GetXseVersion() noexcept -> REX::Version;

	[[nodiscard]]
	auto GetRuntimeVersion() noexcept -> REX::Version;

	[[nodiscard]]
	auto GetSaveFolderName() noexcept -> std::string_view;

	[[nodiscard]]
	auto GetMessagingInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::MessagingInterface*>>;

	[[nodiscard]]
	auto GetScaleformInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::ScaleformInterface*>>;

	[[nodiscard]]
	auto GetPapyrusInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::PapyrusInterface*>>;

	[[nodiscard]]
	auto GetSerializationInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::SerializationInterface*>>;

	[[nodiscard]]
	auto GetTaskInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::TaskInterface*>>;

	[[nodiscard]]
	auto GetObjectInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::ObjectInterface*>>;

	[[nodiscard]]
	auto GetDelayFunctorManager() noexcept -> REX::NotNull<REX::Observer<const F4SE::DelayFunctorManager*>>;

	[[nodiscard]]
	auto GetObjectRegistry() noexcept -> REX::NotNull<REX::Observer<const F4SE::ObjectRegistry*>>;

	[[nodiscard]]
	auto GetPersistentObjectStorage() noexcept -> REX::NotNull<REX::Observer<const F4SE::PersistentObjectStorage*>>;

	[[nodiscard]]
	auto GetTrampolineInterface() noexcept -> REX::NotNull<REX::Observer<const F4SE::TrampolineInterface*>>;

	[[nodiscard]]
	auto GetTrampoline() noexcept -> REX::NotNull<std::shared_ptr<REL::Trampoline>>;

	[[nodiscard]]
	auto GetHookList() noexcept -> REX::NotNull<std::shared_ptr<REL::HookList>>;

	[[nodiscard]]
	auto GetSharedObjectFactoryList() noexcept -> REX::NotNull<std::shared_ptr<F4SE::ISharedObjectFactoryList>>;

	[[nodiscard]]
	auto GetScriptLogEventSink() noexcept -> REX::NotNull<std::shared_ptr<RE::BSTEventSink<RE::BSScript::LogEvent>>>;

	[[nodiscard]]
	auto GetMenuInfoMap() noexcept -> REX::NotNull<std::shared_ptr<F4SE::Menus::IMenuInfoMap>>;

	[[nodiscard]]
	auto GetMenuAssetLoaderMap() noexcept -> REX::NotNull<std::shared_ptr<F4SE::Menus::IMenuAssetLoaderMap>>;

	[[nodiscard]]
	auto GetOrCreateTranslator() -> std::optional<F4SE::Translator>;
}

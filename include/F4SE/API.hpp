#pragma once

#include "F4SE/Core.hpp"

#include "REX/Enum.hpp"
#include "REX/NotNull.hpp"
#include "REX/Version.hpp"

namespace REX
{
	enum class LogLevel : std::int32_t;
}

namespace F4SE
{
	class PreLoadInterface;
	class LoadInterface;
	class PluginInfo;
	class MessagingInterface;
	class ScaleformInterface;
	class PapyrusInterface;
	class SerializationInterface;
	class TaskInterface;
	class ObjectInterface;
	class DelayFunctorManager;
	class ObjectRegistry;
	class PersistentObjectStorage;
	class TrampolineInterface;

	inline constexpr auto ROOT_DIRECTORY_PATH = "."sv;
	inline constexpr auto DATA_DIRECTORY_PATH = "Data"sv;
	inline constexpr auto PLUGINS_DIRECTORY_PATH = "Data/F4SE/Plugins"sv;

	class InitInfo final
	{
	public:
		std::string logName;
		std::string logFileName;
		std::string logFormat;
		REX::Enum<REX::LogLevel> logLevel{
#if NDEBUG == 0
			REX::LogLevel::kDebug
#else
			REX::LogLevel::kInformation
#endif
		};
		std::size_t logFileCount{ std::numeric_limits<std::size_t>::max() };
		std::size_t logFileSize{ std::numeric_limits<std::size_t>::max() };
		bool useHooks{ false };
		bool useTrampoline{ false };
		std::size_t trampolineSize{ 0 };
	};

	void Init(REX::NotNull<const PreLoadInterface*> a_interface, const InitInfo& a_info = {});
	void Init(REX::NotNull<const LoadInterface*> a_interface, const InitInfo& a_info = {});

	bool RegisterForOnPreLoad(REX::NotNull<std::function<void()>> a_callback);
	bool RegisterForOnLoad(REX::NotNull<std::function<void()>> a_callback);

	[[nodiscard]] auto GetInitInfo() noexcept
		-> const InitInfo&;
	[[nodiscard]] auto GetPluginHandle() noexcept
		-> PluginHandle;
	[[nodiscard]] auto GetPluginName() noexcept
		-> std::string_view;
	[[nodiscard]] auto GetPluginAuthor() noexcept
		-> std::string_view;
	[[nodiscard]] auto GetPluginVersion() noexcept
		-> REX::Version;
	[[nodiscard]] auto GetPluginInfo(const char* a_name) noexcept
		-> const PluginInfo*;
	[[nodiscard]] auto GetReleaseIndex() noexcept
		-> std::uint32_t;
	[[nodiscard]] auto GetF4SEVersion() noexcept
		-> REX::Version;
	[[nodiscard]] auto GetRuntimeVersion() noexcept
		-> REX::Version;
	[[nodiscard]] auto GetSaveFolderName() noexcept
		-> std::string_view;
	[[nodiscard]] auto GetLogDirectoryPath() noexcept
		-> const std::filesystem::path&;

	[[nodiscard]] auto GetMessagingInterface() noexcept
		-> REX::NotNull<const MessagingInterface*>;
	[[nodiscard]] auto GetScaleformInterface() noexcept
		-> REX::NotNull<const ScaleformInterface*>;
	[[nodiscard]] auto GetPapyrusInterface() noexcept
		-> REX::NotNull<const PapyrusInterface*>;
	[[nodiscard]] auto GetSerializationInterface() noexcept
		-> REX::NotNull<const SerializationInterface*>;
	[[nodiscard]] auto GetTaskInterface() noexcept
		-> REX::NotNull<const TaskInterface*>;
	[[nodiscard]] auto GetObjectInterface() noexcept
		-> REX::NotNull<const ObjectInterface*>;
	[[nodiscard]] auto GetDelayFunctorManager() noexcept
		-> REX::NotNull<const DelayFunctorManager*>;
	[[nodiscard]] auto GetObjectRegistry() noexcept
		-> REX::NotNull<const ObjectRegistry*>;
	[[nodiscard]] auto GetPersistentObjectStorage() noexcept
		-> REX::NotNull<const PersistentObjectStorage*>;
	[[nodiscard]] auto GetTrampolineInterface() noexcept
		-> REX::NotNull<const TrampolineInterface*>;
}

#include "F4SE/API.hpp"

#include "F4SE/Interfaces.hpp"
#include "F4SE/Logger.hpp"
#include "F4SE/Trampoline.hpp"

namespace F4SE
{
	namespace detail
	{
		struct APIStorage
		{
		public:
			APIStorage(const APIStorage&) = delete;
			APIStorage(APIStorage&&) = delete;

			APIStorage& operator=(const APIStorage&) = delete;
			APIStorage& operator=(APIStorage&&) = delete;

			static APIStorage& get() noexcept
			{
				static APIStorage singleton;
				return singleton;
			}

			std::string_view pluginName{};
			std::string_view pluginAuthor{};
			REL::Version pluginVersion{};

			REL::Version f4seVersion{};
			PluginHandle pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t releaseIndex{ 0 };
			std::function<const void*(F4SEAPI)(const char*)> pluginInfoAccessor;
			std::string_view saveFolderName{};

			MessagingInterface* messagingInterface{ nullptr };
			ScaleformInterface* scaleformInterface{ nullptr };
			PapyrusInterface* papyrusInterface{ nullptr };
			SerializationInterface* serializationInterface{ nullptr };
			TaskInterface* taskInterface{ nullptr };
			ObjectInterface* objectInterface{ nullptr };
			TrampolineInterface* trampolineInterface{ nullptr };

		private:
			APIStorage() noexcept = default;
			~APIStorage() noexcept = default;
		};

		template <class T>
		T* QueryInterface(const LoadInterface* a_intfc, std::uint32_t a_id) noexcept
		{
			auto result = static_cast<T*>(a_intfc->QueryInterface(a_id));
			if (result && result->Version() > T::kVersion) {
				log::warn("interface definition is out of date"sv);
			}
			return result;
		}
	}

	void Init(const LoadInterface* a_intfc, const bool a_log) noexcept
	{
		if (!a_intfc) {
			stl::report_and_fail("interface is null"sv);
		}

		(void)REL::Module::get();
		(void)REL::IDDB::get();

		auto& storage = detail::APIStorage::get();
		const auto& intfc = *a_intfc;

		if (const auto pluginVersionData = PluginVersionData::GetSingleton()) {
			storage.pluginName = pluginVersionData->GetPluginName();
			storage.pluginAuthor = pluginVersionData->GetAuthorName();
			storage.pluginVersion = pluginVersionData->GetPluginVersion();
		}

		storage.f4seVersion = intfc.F4SEVersion();
		storage.pluginHandle = intfc.GetPluginHandle();
		storage.releaseIndex = intfc.GetReleaseIndex();
		storage.pluginInfoAccessor = reinterpret_cast<const detail::F4SEInterface&>(intfc).GetPluginInfo;
		storage.saveFolderName = intfc.GetSaveFolderName();

		if (a_log) {
			log::init();
			log::info("{} v{}"sv, GetPluginName(), GetPluginVersion());
		}

		storage.messagingInterface = detail::QueryInterface<MessagingInterface>(a_intfc, LoadInterface::kMessaging);
		storage.scaleformInterface = detail::QueryInterface<ScaleformInterface>(a_intfc, LoadInterface::kScaleform);
		storage.papyrusInterface = detail::QueryInterface<PapyrusInterface>(a_intfc, LoadInterface::kPapyrus);
		storage.serializationInterface = detail::QueryInterface<SerializationInterface>(a_intfc, LoadInterface::kSerialization);
		storage.taskInterface = detail::QueryInterface<TaskInterface>(a_intfc, LoadInterface::kTask);
		storage.objectInterface = detail::QueryInterface<ObjectInterface>(a_intfc, LoadInterface::kObject);
		storage.trampolineInterface = detail::QueryInterface<TrampolineInterface>(a_intfc, LoadInterface::kTrampoline);
	}

	std::string_view GetPluginName() noexcept
	{
		return detail::APIStorage::get().pluginName;
	}

	std::string_view GetPluginAuthor() noexcept
	{
		return detail::APIStorage::get().pluginAuthor;
	}

	REL::Version GetPluginVersion() noexcept
	{
		return detail::APIStorage::get().pluginVersion;
	}

	REL::Version GetF4SEVersion() noexcept
	{
		return detail::APIStorage::get().f4seVersion;
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return detail::APIStorage::get().pluginHandle;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return detail::APIStorage::get().releaseIndex;
	}

	std::optional<PluginInfo> GetPluginInfo(stl::zstring a_plugin) noexcept
	{
		const auto& accessor = detail::APIStorage::get().pluginInfoAccessor;
		if (accessor) {
			const auto result = accessor(a_plugin.data());
			if (result) {
				return *static_cast<const PluginInfo*>(result);
			}
		}

		log::warn("failed to get plugin info for {}"sv, a_plugin);
		return std::nullopt;
	}

	std::string_view GetSaveFolderName() noexcept
	{
		return detail::APIStorage::get().saveFolderName;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return detail::APIStorage::get().messagingInterface;
	}

	const ScaleformInterface* GetScaleformInterface() noexcept
	{
		return detail::APIStorage::get().scaleformInterface;
	}

	const PapyrusInterface* GetPapyrusInterface() noexcept
	{
		return detail::APIStorage::get().papyrusInterface;
	}

	const SerializationInterface* GetSerializationInterface() noexcept
	{
		return detail::APIStorage::get().serializationInterface;
	}

	const TaskInterface* GetTaskInterface() noexcept
	{
		return detail::APIStorage::get().taskInterface;
	}

	const ObjectInterface* GetObjectInterface() noexcept
	{
		return detail::APIStorage::get().objectInterface;
	}

	const TrampolineInterface* GetTrampolineInterface() noexcept
	{
		return detail::APIStorage::get().trampolineInterface;
	}

	void AllocTrampoline(std::size_t a_size) noexcept
	{
		auto& trampoline = GetTrampoline();
		const auto interface = GetTrampolineInterface();
		const auto mem = interface ? interface->AllocateFromBranchPool(a_size) : nullptr;
		if (mem) {
			trampoline.set_trampoline(mem, a_size);
		}
		else {
			trampoline.create(a_size);
		}
	}
}

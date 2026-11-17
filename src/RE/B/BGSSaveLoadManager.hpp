#pragma once

#include "RE/B/BGSSaveLoadThread.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSaveDataSystemUtility.hpp"
#include "RE/B/BSSaveDataSystemUtilityImage.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::SPECIALMenuEvent
{
	class NameChangedEvent;
}

namespace RE
{
	class BGSSaveLoadFile;
	class BGSSaveLoadFileEntry;
	class NiTexture;
	class Setting;

	class __declspec(novtable) BGSSaveLoadManager : public BSTEventSink<SPECIALMenuEvent::NameChangedEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSaveLoadManager;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSaveLoadManager;

		inline static constexpr auto SAVE_FILE_EXTENSION = ".fos"sv;
		inline static constexpr auto TEMP_FILE_EXTENSION = ".tmp"sv;
		inline static constexpr auto BACKUP_FILE_EXTENSION = ".bak"sv;

		inline static constexpr auto AUTO_SAVE_NAME = "Autosave"sv;
		inline static constexpr auto EXIT_SAVE_NAME = "Exitsave"sv;
		inline static constexpr auto GENERATED_SAVE_NAME = "Save"sv;
		inline static constexpr auto QUICK_SAVE_NAME = "Quicksave"sv;

		enum class QUEUED_TASK : std::int32_t
		{
			None = 0,
			AutoSave = 1 << 0,
			ForceSave = 1 << 1,
			LoadMostRecentSave = 1 << 2,
			Quicksave = 1 << 3,
			Quickload = 1 << 4,
			QuickNewSave = 1 << 5,
			LoadGame = 1 << 6,
			SysUtilLoadGame = 1 << 7,
			MissingContentLoad = 1 << 8,
			AutosaveCommit = 1 << 9,
			QuicksaveCommit = 1 << 10,
			CaptureFaceGen = 1 << 11,
			BuildSaveGameList = 1 << 12,
			RefreshScreenshot = 1 << 13,
			SaveAndQuit = 1 << 14,
			ConfirmModsLoad = 1 << 15,
			SaveAndQuitToDesktop = 1 << 16
		};

		enum class SAVEFILE_CATEGORY : std::int32_t
		{
			User = 0,
			Auto = 1,
			Quick = 2,
			Exit = 3
		};

		enum class SAVEFILE_TYPE : std::int32_t
		{
			Screenshot = 0,
			Load = 1,
			Save = 2
		};

		~BGSSaveLoadManager() override; // 0x00

		// override (BSTEventSink)
		auto ProcessEvent(
			const SPECIALMenuEvent::NameChangedEvent& a_event,
			BSTEventSource<SPECIALMenuEvent::NameChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSSaveLoadManager*;

		auto Autosave() -> bool;
		void BufferSceneScreenShot();
		void BuildSaveGameList(std::uint64_t a_playerID);
		auto DeleteSaveFile(const char* a_fileName, bool a_checkHasSaveData = true) -> bool;
		auto ForceSave() -> bool;
		void GenerateSaveFileName(char* a_saveFileName, SAVEFILE_CATEGORY a_saveCategory, bool a_displayOnly = false);
		void GetFullPath(const char* a_fileName, char* a_fullPath, bool a_tempFile = false) const;
		void GetSaveDirectoryPath(char* a_path) const;
		[[nodiscard]]
		auto IsAutoSavingAllowed() const -> bool;
		[[nodiscard]]
		auto IsLoadingAllowed() const -> bool;
		[[nodiscard]]
		auto IsSaveFileExistent(const char* a_fileName) const -> bool;
		[[nodiscard]]
		auto IsSavingAllowed() const -> bool;
		auto LoadGame(const char* a_fileName, bool a_checkForMods = true, bool a_ignoreMissingContent = false) -> bool;
		void QueueSaveLoadTask(QUEUED_TASK a_task);
		auto Quickload() -> bool;
		auto Quicksave() -> bool;
		auto SaveGame(const char* a_fileName = nullptr, bool a_compress = false) -> bool;

		auto CreateCompleteAutosave(bool a_silent = false) -> bool;
		auto CreateCompleteQuicksave(bool a_silent = false) -> bool;
		auto CreateCompleteFullSave(bool a_silent = false) -> bool;
		auto CreateCompleteCustomSave(const char* a_fileName, bool a_silent = false) -> bool;

		[[nodiscard]]
		static auto IsSaveFileNameAutosave(std::string_view a_fileName) noexcept -> bool;
		[[nodiscard]]
		static auto IsSaveFileNameCustom(std::string_view a_fileName) noexcept -> bool;
		[[nodiscard]]
		static auto IsSaveFileNameExitSave(std::string_view a_fileName) noexcept -> bool;
		[[nodiscard]]
		static auto IsSaveFileNameGenerated(std::string_view a_fileName) noexcept -> bool;
		[[nodiscard]]
		static auto IsSaveFileNameQuicksave(std::string_view a_fileName) noexcept -> bool;

		[[nodiscard]]
		static auto GetDisableAutoSaveSetting() -> Setting&;
		[[nodiscard]]
		static auto GetDisableAutoSave() -> bool;
		static void SetDisableAutoSave(bool a_value);

		[[nodiscard]]
		static auto GetAutoSavingMessageSetting() -> Setting&;
		[[nodiscard]]
		static auto GetCannotSaveMessageSetting() -> Setting&;
		[[nodiscard]]
		static auto GetQuicksaveMessageSetting() -> Setting&;
		[[nodiscard]]
		static auto GetSaveMessageSetting() -> Setting&;
		[[nodiscard]]
		static auto GetSaveFailedMessageSetting() -> Setting&;

		[[nodiscard]]
		static auto GetAutosaveMessage() -> BSFixedStringCS;
		[[nodiscard]]
		static auto GetCannotSaveMessage() -> BSFixedStringCS;
		[[nodiscard]]
		static auto GetQuicksaveMessage() -> BSFixedStringCS;
		[[nodiscard]]
		static auto GetSaveMessage() -> BSFixedStringCS;
		[[nodiscard]]
		static auto GetSaveFailedMessage() -> BSFixedStringCS;

		void AutosaveImpl(bool a_background);
		void DeleteSaveFileImpl(const char* a_fileName, std::int32_t a_deviceID, bool a_checkHasSaveData);
		void GenerateSaveFileNameImpl(char* a_saveFileName, bool a_displayOnly, SAVEFILE_CATEGORY a_saveCategory);
		auto LoadGameImpl(
			const char* a_fileName,
			std::int32_t a_deviceID,
			std::uint32_t a_outputStats,
			bool a_checkForMods,
			bool a_ignoreMissingContent) -> bool;
		auto SaveGameImpl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_compress)
			-> bool;

		// members
		BSTArray<BGSSaveLoadFileEntry*> saveGameList;								   // 0x008
		bool isSaveListBuilt;														   // 0x020
		std::uint32_t saveGameCount;												   // 0x024
		std::uint32_t currentSaveGameNumber;										   // 0x028
		std::uint64_t saveGameListBuildID;											   // 0x030
		std::uint32_t currentAutoSaveNumber;										   // 0x038
		bool simulatedMode;															   // 0x03C
		bool autosaveDisabledForDiskspace;											   // 0x03D
		REX::Enum<QUEUED_TASK, std::int32_t> queuedTasks;							   // 0x040
		std::uint32_t saveOperationDelayCounter;									   // 0x044
		BGSSaveLoadFileEntry* queuedEntryToLoad;									   // 0x048
		std::uint64_t lastSaveTime;													   // 0x050
		bool savingAllowed;															   // 0x058
		char* mostRecentSaveGame;													   // 0x060
		std::int32_t mostRecentSaveGameDeviceID;									   // 0x068
		BSTHashMap<std::uint64_t, BSFixedString> playerIDNameMap;					   // 0x070
		BSTHashMap<BSFixedString, BSFixedString> editorIDLocationMap;				   // 0x0A0
		std::uint64_t currentPlayerID;												   // 0x0D0
		std::uint64_t displayPlayerID;												   // 0x0D8
		BSFixedString savefileNameToDelete;											   // 0x0E0
		BSTHashMap<std::uint32_t, BSFixedString> autosaveFileNames;					   // 0x0E8
		BSFixedString quicksaveFileName;											   // 0x118
		BSFixedString exitsaveFileName;												   // 0x120
		bool hasSaveData;															   // 0x128
		BGSSaveLoadFile* saveLoadFile;												   // 0x130
		bool returnedFromSysUtil;													   // 0x138
		bool sysUtilLoadDataComplete;												   // 0x139
		BSSaveDataSystemUtility::SaveCompleteCallbackType sysUtilSaveCompleteCallback; // 0x140
		BSSaveDataSystemUtility::LoadCompleteCallbackType sysUtilLoadCompleteCallback; // 0x148
		BSSaveDataSystemUtilityImage saveDataCreateImage;							   // 0x150
		BSSaveDataSystemUtilityImage saveDataBackgroundImage;						   // 0x168
		BSSaveDataSystemUtilityImage saveDataIconEncodedImage;						   // 0x180
		std::array<NiPointer<NiTexture>, 1> screenshot;								   // 0x198
		BGSSaveLoadThread saveLoadTasksThread;										   // 0x200
	};

	static_assert(sizeof(BGSSaveLoadManager) == 0x980);
}

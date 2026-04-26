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

	class __declspec(novtable) BGSSaveLoadManager
		: public BSTEventSink<SPECIALMenuEvent::NameChangedEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSaveLoadManager };
		inline static constexpr auto VTABLE{ VTABLE::BGSSaveLoadManager };

		inline static constexpr auto SAVE_FILE_EXTENSION = ".fos"sv;
		inline static constexpr auto TEMP_FILE_EXTENSION = ".tmp"sv;
		inline static constexpr auto BACKUP_FILE_EXTENSION = ".bak"sv;

		inline static constexpr auto AUTO_SAVE_NAME = "Autosave"sv;
		inline static constexpr auto EXIT_SAVE_NAME = "Exitsave"sv;
		inline static constexpr auto GENERATED_SAVE_NAME = "Save"sv;
		inline static constexpr auto QUICK_SAVE_NAME = "Quicksave"sv;

		enum class QUEUED_TASK : std::int32_t
		{
			kNone = 0,
			kAutoSave = 1 << 0,
			kForceSave = 1 << 1,
			kLoadMostRecentSave = 1 << 2,
			kQuicksave = 1 << 3,
			kQuickload = 1 << 4,
			kQuickNewSave = 1 << 5,
			kLoadGame = 1 << 6,
			kSysUtilLoadGame = 1 << 7,
			kMissingContentLoad = 1 << 8,
			kAutosaveCommit = 1 << 9,
			kQuicksaveCommit = 1 << 10,
			kCaptureFaceGen = 1 << 11,
			kBuildSaveGameList = 1 << 12,
			kRefreshScreenshot = 1 << 13,
			kSaveAndQuit = 1 << 14,
			kConfirmModsLoad = 1 << 15,
			kSaveAndQuitToDesktop = 1 << 16
		};

		enum class SAVEFILE_CATEGORY : std::int32_t
		{
			kUser = 0,
			kAuto = 1,
			kQuick = 2,
			kExit = 3
		};

		enum class SAVEFILE_TYPE : std::int32_t
		{
			kScreenshot = 0,
			kLoad = 1,
			kSave = 2
		};

		~BGSSaveLoadManager() override; // 00

		// override (BSTEventSink)
		BSEventNotifyControl ProcessEvent(const SPECIALMenuEvent::NameChangedEvent& a_event, BSTEventSource<SPECIALMenuEvent::NameChangedEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BGSSaveLoadManager* GetSingleton();

		bool Autosave();
		void BufferSceneScreenShot();
		void BuildSaveGameList(std::uint64_t a_playerID);
		bool DeleteSaveFile(const char* a_fileName, bool a_checkHasSaveData = true);
		bool ForceSave();
		void GenerateSaveFileName(char* a_saveFileName, SAVEFILE_CATEGORY a_saveCategory, bool a_displayOnly = false);
		void GetFullPath(const char* a_fileName, char* a_fullPath, bool a_tempFile = false) const;
		void GetSaveDirectoryPath(char* a_path) const;
		[[nodiscard]] bool IsAutoSavingAllowed() const;
		[[nodiscard]] bool IsLoadingAllowed() const;
		[[nodiscard]] bool IsSaveFileExistent(const char* a_fileName) const;
		[[nodiscard]] bool IsSavingAllowed() const;
		bool LoadGame(const char* a_fileName, bool a_checkForMods = true, bool a_ignoreMissingContent = false);
		void QueueSaveLoadTask(QUEUED_TASK a_task);
		bool Quickload();
		bool Quicksave();
		bool SaveGame(const char* a_fileName = nullptr, bool a_compress = false);

		bool CreateCompleteAutosave(bool a_silent = false);
		bool CreateCompleteQuicksave(bool a_silent = false);
		bool CreateCompleteFullSave(bool a_silent = false);
		bool CreateCompleteCustomSave(const char* a_fileName, bool a_silent = false);

		[[nodiscard]] static bool IsSaveFileNameAutosave(std::string_view a_fileName) noexcept;
		[[nodiscard]] static bool IsSaveFileNameCustom(std::string_view a_fileName) noexcept;
		[[nodiscard]] static bool IsSaveFileNameExitSave(std::string_view a_fileName) noexcept;
		[[nodiscard]] static bool IsSaveFileNameGenerated(std::string_view a_fileName) noexcept;
		[[nodiscard]] static bool IsSaveFileNameQuicksave(std::string_view a_fileName) noexcept;

		[[nodiscard]] static Setting& GetDisableAutoSaveSetting();
		[[nodiscard]] static bool GetDisableAutoSave();
		static void SetDisableAutoSave(bool a_value);

		[[nodiscard]] static Setting& GetAutoSavingMessageSetting();
		[[nodiscard]] static Setting& GetCannotSaveMessageSetting();
		[[nodiscard]] static Setting& GetQuicksaveMessageSetting();
		[[nodiscard]] static Setting& GetSaveMessageSetting();
		[[nodiscard]] static Setting& GetSaveFailedMessageSetting();

		[[nodiscard]] static const char* GetAutosaveMessage();
		[[nodiscard]] static const char* GetCannotSaveMessage();
		[[nodiscard]] static const char* GetQuicksaveMessage();
		[[nodiscard]] static const char* GetSaveMessage();
		[[nodiscard]] static const char* GetSaveFailedMessage();

		void AutosaveImpl(bool a_background);
		void DeleteSaveFileImpl(const char* a_fileName, std::int32_t a_deviceID, bool a_checkHasSaveData);
		void GenerateSaveFileNameImpl(char* a_saveFileName, bool a_displayOnly, SAVEFILE_CATEGORY a_saveCategory);
		bool LoadGameImpl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_checkForMods, bool a_ignoreMissingContent);
		bool SaveGameImpl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_compress);

		// members
		BSTArray<BGSSaveLoadFileEntry*> saveGameList;								   // 008
		bool isSaveListBuilt;														   // 020
		std::uint32_t saveGameCount;												   // 024
		std::uint32_t currentSaveGameNumber;										   // 028
		std::uint64_t saveGameListBuildID;											   // 030
		std::int32_t currentAutoSaveNumber;											   // 038
		bool simulatedMode;															   // 03C
		bool autosaveDisabledForDiskspace;											   // 03D
		REX::Enum<QUEUED_TASK, std::int32_t> queuedTasks;							   // 040
		std::uint32_t saveOperationDelayCounter;									   // 044
		BGSSaveLoadFileEntry* queuedEntryToLoad;									   // 048
		std::uint64_t lastSaveTime;													   // 050
		bool savingAllowed;															   // 058
		char* mostRecentSaveGame;													   // 060
		std::int32_t mostRecentSaveGameDeviceID;									   // 068
		BSTHashMap<std::uint64_t, BSFixedString> playerIDNameMap;					   // 070
		BSTHashMap<BSFixedString, BSFixedString> editorIDLocationMap;				   // 0A0
		std::uint64_t currentPlayerID;												   // 0D0
		std::uint64_t displayPlayerID;												   // 0D8
		BSFixedString savefileNameToDelete;											   // 0E0
		BSTHashMap<std::uint32_t, BSFixedString> autosaveFileNames;					   // 0E8
		BSFixedString quicksaveFileName;											   // 118
		BSFixedString exitsaveFileName;												   // 120
		bool hasSaveData;															   // 128
		BGSSaveLoadFile* saveLoadFile;												   // 130
		bool returnedFromSysUtil;													   // 138
		bool sysUtilLoadDataComplete;												   // 139
		BSSaveDataSystemUtility::SaveCompleteCallbackType sysUtilSaveCompleteCallback; // 140
		BSSaveDataSystemUtility::LoadCompleteCallbackType sysUtilLoadCompleteCallback; // 148
		BSSaveDataSystemUtilityImage saveDataCreateImage;							   // 150
		BSSaveDataSystemUtilityImage saveDataBackgroundImage;						   // 168
		BSSaveDataSystemUtilityImage saveDataIconEncodedImage;						   // 180
		std::array<NiPointer<NiTexture>, 1> screenshot;								   // 198
		BGSSaveLoadThread saveLoadTasksThread;										   // 200
	};
	static_assert(sizeof(BGSSaveLoadManager) == 0x980);
}

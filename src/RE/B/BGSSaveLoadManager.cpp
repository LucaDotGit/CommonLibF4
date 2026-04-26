#include "RE/B/BGSSaveLoadManager.hpp"

#include "RE/S/SendHUDMessage.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	static constexpr auto SAVE_IN_BACKGROUND = false;
	static constexpr auto DEVICE_ID = static_cast<std::int32_t>(-1);
	static constexpr auto OUTPUT_STATS = static_cast<std::uint32_t>(0);

	BGSSaveLoadManager* BGSSaveLoadManager::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<BGSSaveLoadManager**>{ ID::BGSSaveLoadManager::Singleton };
		return *SINGLETON;
	}

	void BGSSaveLoadManager::BuildSaveGameList(std::uint64_t a_playerID)
	{
		using FuncType = decltype(&BGSSaveLoadManager::BuildSaveGameList);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::BuildSaveGameList };
		FUNC(this, a_playerID);
	}

	bool BGSSaveLoadManager::Autosave()
	{

		const auto oldSaveNumber = currentAutoSaveNumber;
		AutosaveImpl(SAVE_IN_BACKGROUND);
		const auto newSaveNumber = currentAutoSaveNumber;

		return newSaveNumber != oldSaveNumber;
	}

	void BGSSaveLoadManager::BufferSceneScreenShot()
	{
		using FuncType = void (BGSSaveLoadManager::*)();
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::BufferSceneScreenShot };
		FUNC(this);
	}

	bool BGSSaveLoadManager::DeleteSaveFile(const char* a_fileName, bool a_checkHasSaveData)
	{
		DeleteSaveFileImpl(a_fileName, DEVICE_ID, a_checkHasSaveData);
		return REX::W32::GetLastError() == REX::W32::ERROR_CODE_SUCCESS;
	}

	bool BGSSaveLoadManager::ForceSave()
	{
		return SaveGame();
	}

	void BGSSaveLoadManager::GenerateSaveFileName(char* a_saveFileName, SAVEFILE_CATEGORY a_saveCategory, bool a_displayOnly)
	{
		GenerateSaveFileNameImpl(a_saveFileName, a_displayOnly, a_saveCategory);
	}

	void BGSSaveLoadManager::GetFullPath(const char* a_fileName, char* a_fullPath, bool a_tempFile) const
	{
		using FuncType = decltype(&BGSSaveLoadManager::GetFullPath);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::GetFullPath };
		FUNC(this, a_fileName, a_fullPath, a_tempFile);
	}

	void BGSSaveLoadManager::GetSaveDirectoryPath(char* a_path) const
	{
		using FuncType = decltype(&BGSSaveLoadManager::GetSaveDirectoryPath);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::GetSaveDirectoryPath };
		FUNC(this, a_path);
	}

	bool BGSSaveLoadManager::IsAutoSavingAllowed() const
	{
		return !GetDisableAutoSave() && IsSavingAllowed();
	}

	bool BGSSaveLoadManager::IsLoadingAllowed() const
	{
		using FuncType = decltype(&BGSSaveLoadManager::IsLoadingAllowed);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::IsLoadingAllowed };
		return std::invoke(FUNC, this);
	}

	bool BGSSaveLoadManager::IsSaveFileExistent(const char* a_fileName) const
	{
		auto fullPath = std::array<char, REX::W32::MAX_PATH>();
		GetFullPath(a_fileName, fullPath.data());
		return _access(fullPath.data(), 0) != -1;
	}

	bool BGSSaveLoadManager::IsSavingAllowed() const
	{
		using FuncType = decltype(&BGSSaveLoadManager::IsSavingAllowed);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::IsSavingAllowed };
		return std::invoke(FUNC, this);
	}

	bool BGSSaveLoadManager::LoadGame(const char* a_fileName, bool a_checkForMods, bool a_ignoreMissingContent)
	{
		return LoadGameImpl(a_fileName, DEVICE_ID, OUTPUT_STATS, a_checkForMods, a_ignoreMissingContent);
	}

	void BGSSaveLoadManager::QueueSaveLoadTask(QUEUED_TASK a_task)
	{
		using FuncType = decltype(&BGSSaveLoadManager::QueueSaveLoadTask);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::QueueSaveLoadTask };
		FUNC(this, a_task);
	}

	bool BGSSaveLoadManager::Quickload()
	{
		using FuncType = decltype(&BGSSaveLoadManager::Quickload);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::Quickload };
		return std::invoke(FUNC, this);
	}

	bool BGSSaveLoadManager::Quicksave()
	{
		using FuncType = decltype(&BGSSaveLoadManager::Quicksave);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::Quicksave };
		return std::invoke(FUNC, this);
	}

	bool BGSSaveLoadManager::SaveGame(const char* a_fileName, bool a_compress)
	{
		return SaveGameImpl(a_fileName, DEVICE_ID, OUTPUT_STATS, a_compress);
	}

	bool BGSSaveLoadManager::CreateCompleteAutosave(bool a_silent)
	{
		if (!IsAutoSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetAutosaveMessage());
		}

		if (Autosave()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage());
		}

		return false;
	}

	bool BGSSaveLoadManager::CreateCompleteQuicksave(bool a_silent)
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetQuicksaveMessage());
		}

		if (Quicksave()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage());
		}

		return false;
	}

	bool BGSSaveLoadManager::CreateCompleteFullSave(bool a_silent)
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveMessage());
		}

		if (SaveGame()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage());
		}

		return false;
	}

	bool BGSSaveLoadManager::CreateCompleteCustomSave(const char* a_fileName, bool a_silent)
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveMessage());
		}

		if (SaveGame(a_fileName)) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage());
		}

		return false;
	}

	bool BGSSaveLoadManager::IsSaveFileNameAutosave(std::string_view a_fileName) noexcept
	{
		return REX::ContainsIgnoreCase(a_fileName, AUTO_SAVE_NAME);
	}

	bool BGSSaveLoadManager::IsSaveFileNameCustom(std::string_view a_fileName) noexcept
	{
		return !IsSaveFileNameAutosave(a_fileName) &&
			   !IsSaveFileNameExitSave(a_fileName) &&
			   !IsSaveFileNameGenerated(a_fileName) &&
			   !IsSaveFileNameQuicksave(a_fileName);
	}

	bool BGSSaveLoadManager::IsSaveFileNameExitSave(std::string_view a_fileName) noexcept
	{
		return REX::ContainsIgnoreCase(a_fileName, EXIT_SAVE_NAME);
	}

	bool BGSSaveLoadManager::IsSaveFileNameGenerated(std::string_view a_fileName) noexcept
	{
		return REX::ContainsIgnoreCase(a_fileName, GENERATED_SAVE_NAME);
	}

	bool BGSSaveLoadManager::IsSaveFileNameQuicksave(std::string_view a_fileName) noexcept
	{
		return REX::ContainsIgnoreCase(a_fileName, QUICK_SAVE_NAME);
	}

	Setting& BGSSaveLoadManager::GetDisableAutoSaveSetting()
	{
		static auto* DisableAutoSave = GetINISetting("bDisableAutoSave:SaveGame"sv);
		return *DisableAutoSave;
	}

	bool BGSSaveLoadManager::GetDisableAutoSave()
	{
		const auto& setting = GetDisableAutoSaveSetting();
		if (!setting.IsBinary()) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		return setting.GetBinary();
	}

	void BGSSaveLoadManager::SetDisableAutoSave(bool a_value)
	{
		auto& setting = GetDisableAutoSaveSetting();
		if (!setting.IsBinary()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetBinary(a_value);
	}

	Setting& BGSSaveLoadManager::GetAutoSavingMessageSetting()
	{
		static auto* AutoSaving = GetGameSetting("sAutoSaving"sv);
		return *AutoSaving;
	}

	Setting& BGSSaveLoadManager::GetCannotSaveMessageSetting()
	{
		static auto* CannotSaveNow = GetGameSetting("sCantSaveNow"sv);
		return *CannotSaveNow;
	}

	Setting& BGSSaveLoadManager::GetQuicksaveMessageSetting()
	{
		static auto* QuickSaving = GetGameSetting("sQuickSaving"sv);
		return *QuickSaving;
	}

	Setting& BGSSaveLoadManager::GetSaveMessageSetting()
	{
		static auto* MenuDisplayShortXBoxSaveMessage = GetGameSetting("sMenuDisplayShortXBoxSaveMessage"sv);
		return *MenuDisplayShortXBoxSaveMessage;
	}

	Setting& BGSSaveLoadManager::GetSaveFailedMessageSetting()
	{
		static auto* SaveFailed = GetGameSetting("sSaveFailed"sv);
		return *SaveFailed;
	}

	const char* BGSSaveLoadManager::GetAutosaveMessage()
	{
		const auto& setting = GetAutoSavingMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return setting.GetString();
	}

	const char* BGSSaveLoadManager::GetCannotSaveMessage()
	{
		const auto& setting = GetCannotSaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return setting.GetString();
	}

	const char* BGSSaveLoadManager::GetQuicksaveMessage()
	{
		const auto& setting = GetQuicksaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return setting.GetString();
	}

	const char* BGSSaveLoadManager::GetSaveMessage()
	{
		const auto& setting = GetSaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return setting.GetString();
	}

	const char* BGSSaveLoadManager::GetSaveFailedMessage()
	{
		const auto& setting = GetSaveFailedMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return setting.GetString();
	}

	void BGSSaveLoadManager::AutosaveImpl(bool a_background)
	{
		using FuncType = decltype(&BGSSaveLoadManager::AutosaveImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::AutosaveImpl };
		FUNC(this, a_background);
	}

	void BGSSaveLoadManager::DeleteSaveFileImpl(const char* a_fileName, std::int32_t a_deviceID, bool a_checkHasSaveData)
	{
		using FuncType = decltype(&BGSSaveLoadManager::DeleteSaveFileImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::DeleteSaveFileImpl };
		FUNC(this, a_fileName, a_deviceID, a_checkHasSaveData);
	}

	void BGSSaveLoadManager::GenerateSaveFileNameImpl(char* a_saveFileName, bool a_displayOnly, SAVEFILE_CATEGORY a_saveCategory)
	{
		using FuncType = decltype(&BGSSaveLoadManager::GenerateSaveFileNameImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::GenerateSaveFileNameImpl };
		FUNC(this, a_saveFileName, a_displayOnly, a_saveCategory);
	}

	bool BGSSaveLoadManager::LoadGameImpl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_checkForMods, bool a_ignoreMissingContent)
	{
		using FuncType = decltype(&BGSSaveLoadManager::LoadGameImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::LoadGameImpl };
		return std::invoke(FUNC, this, a_fileName, a_deviceID, a_outputStats, a_checkForMods, a_ignoreMissingContent);
	}

	bool BGSSaveLoadManager::SaveGameImpl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_compress)
	{
		using FuncType = decltype(&BGSSaveLoadManager::SaveGameImpl);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadManager::SaveGameImpl };
		return std::invoke(FUNC, this, a_fileName, a_deviceID, a_outputStats, a_compress);
	}
}

#include "RE/B/BGSSaveLoadManager.hpp"

#include "RE/S/SendHUDMessage.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	static constexpr auto SAVE_IN_BACKGROUND = false;
	static constexpr auto DEVICE_ID = static_cast<std::int32_t>(-1);
	static constexpr auto OUTPUT_STATS = static_cast<std::uint32_t>(0);

	auto BGSSaveLoadManager::GetSingleton() noexcept -> BGSSaveLoadManager*
	{
		static const auto SINGLETON = REL::Relocation<BGSSaveLoadManager**>(ID::BGSSaveLoadManager::Singleton);
		return *SINGLETON;
	}

	void BGSSaveLoadManager::BuildSaveGameList(std::uint64_t a_playerID)
	{
		using FuncType = decltype(&BGSSaveLoadManager::BuildSaveGameList);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::BuildSaveGameList);
		std::invoke(FUNC, this, a_playerID);
	}

	auto BGSSaveLoadManager::Autosave() -> bool
	{
		const auto oldSaveNumber = currentAutoSaveNumber;
		AutosaveImpl(SAVE_IN_BACKGROUND);
		const auto newSaveNumber = currentAutoSaveNumber;

		return newSaveNumber != oldSaveNumber;
	}

	void BGSSaveLoadManager::BufferSceneScreenShot()
	{
		using FuncType = void (BGSSaveLoadManager::*)();
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::BufferSceneScreenShot);
		std::invoke(FUNC, this);
	}

	auto BGSSaveLoadManager::DeleteSaveFile(const char* a_fileName, bool a_checkHasSaveData) -> bool
	{
		DeleteSaveFileImpl(a_fileName, DEVICE_ID, a_checkHasSaveData);
		return REX::W32::GetLastError() == REX::W32::ERROR_CODE_SUCCESS;
	}

	auto BGSSaveLoadManager::ForceSave() -> bool
	{
		return SaveGame();
	}

	void BGSSaveLoadManager::GenerateSaveFileName(
		char* a_saveFileName,
		SAVEFILE_CATEGORY a_saveCategory,
		bool a_displayOnly)
	{
		GenerateSaveFileNameImpl(a_saveFileName, a_displayOnly, a_saveCategory);
	}

	void BGSSaveLoadManager::GetFullPath(const char* a_fileName, char* a_fullPath, bool a_tempFile) const
	{
		using FuncType = decltype(&BGSSaveLoadManager::GetFullPath);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::GetFullPath);
		std::invoke(FUNC, this, a_fileName, a_fullPath, a_tempFile);
	}

	void BGSSaveLoadManager::GetSaveDirectoryPath(char* a_path) const
	{
		using FuncType = decltype(&BGSSaveLoadManager::GetSaveDirectoryPath);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::GetSaveDirectoryPath);
		std::invoke(FUNC, this, a_path);
	}

	auto BGSSaveLoadManager::IsAutoSavingAllowed() const -> bool
	{
		return !GetDisableAutoSave() && IsSavingAllowed();
	}

	auto BGSSaveLoadManager::IsLoadingAllowed() const -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::IsLoadingAllowed);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::IsLoadingAllowed);
		return std::invoke(FUNC, this);
	}

	auto BGSSaveLoadManager::IsSaveFileExistent(const char* a_fileName) const -> bool
	{
		auto fullPath = REX::StaticString<REX::W32::MAX_PATH>();
		GetFullPath(a_fileName, fullPath.data());
		return ::_access(fullPath.data(), 0) != -1;
	}

	auto BGSSaveLoadManager::IsSavingAllowed() const -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::IsSavingAllowed);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::IsSavingAllowed);
		return std::invoke(FUNC, this);
	}

	auto BGSSaveLoadManager::LoadGame(const char* a_fileName, bool a_checkForMods, bool a_ignoreMissingContent) -> bool
	{
		return LoadGameImpl(a_fileName, DEVICE_ID, OUTPUT_STATS, a_checkForMods, a_ignoreMissingContent);
	}

	void BGSSaveLoadManager::QueueSaveLoadTask(QUEUED_TASK a_task)
	{
		using FuncType = decltype(&BGSSaveLoadManager::QueueSaveLoadTask);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::QueueSaveLoadTask);
		std::invoke(FUNC, this, a_task);
	}

	auto BGSSaveLoadManager::Quickload() -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::Quickload);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::Quickload);
		return std::invoke(FUNC, this);
	}

	auto BGSSaveLoadManager::Quicksave() -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::Quicksave);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::Quicksave);
		return std::invoke(FUNC, this);
	}

	auto BGSSaveLoadManager::SaveGame(const char* a_fileName, bool a_compress) -> bool
	{
		return SaveGameImpl(a_fileName, DEVICE_ID, OUTPUT_STATS, a_compress);
	}

	auto BGSSaveLoadManager::CreateCompleteAutosave(bool a_silent) -> bool
	{
		if (!IsAutoSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetAutosaveMessage().data());
		}

		if (Autosave()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage().data());
		}

		return false;
	}

	auto BGSSaveLoadManager::CreateCompleteQuicksave(bool a_silent) -> bool
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetQuicksaveMessage().data());
		}

		if (Quicksave()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage().data());
		}

		return false;
	}

	auto BGSSaveLoadManager::CreateCompleteFullSave(bool a_silent) -> bool
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveMessage().data());
		}

		if (SaveGame()) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage().data());
		}

		return false;
	}

	auto BGSSaveLoadManager::CreateCompleteCustomSave(const char* a_fileName, bool a_silent) -> bool
	{
		if (!IsSavingAllowed()) {
			return false;
		}

		BufferSceneScreenShot();

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveMessage().data());
		}

		if (SaveGame(a_fileName)) {
			return true;
		}

		if (!a_silent) {
			SendHUDMessage::ShowHUDMessage(GetSaveFailedMessage().data());
		}

		return false;
	}

	auto BGSSaveLoadManager::IsSaveFileNameAutosave(std::string_view a_fileName) noexcept -> bool
	{
		return REX::ContainsIgnoreCase(a_fileName, AUTO_SAVE_NAME);
	}

	auto BGSSaveLoadManager::IsSaveFileNameCustom(std::string_view a_fileName) noexcept -> bool
	{
		return !IsSaveFileNameAutosave(a_fileName) &&
			   !IsSaveFileNameExitSave(a_fileName) &&
			   !IsSaveFileNameGenerated(a_fileName) &&
			   !IsSaveFileNameQuicksave(a_fileName);
	}

	auto BGSSaveLoadManager::IsSaveFileNameExitSave(std::string_view a_fileName) noexcept -> bool
	{
		return REX::ContainsIgnoreCase(a_fileName, EXIT_SAVE_NAME);
	}

	auto BGSSaveLoadManager::IsSaveFileNameGenerated(std::string_view a_fileName) noexcept -> bool
	{
		return REX::ContainsIgnoreCase(a_fileName, GENERATED_SAVE_NAME);
	}

	auto BGSSaveLoadManager::IsSaveFileNameQuicksave(std::string_view a_fileName) noexcept -> bool
	{
		return REX::ContainsIgnoreCase(a_fileName, QUICK_SAVE_NAME);
	}

	auto BGSSaveLoadManager::GetDisableAutoSaveSetting() -> Setting&
	{
		static auto* DisableAutoSave = GetINISetting("bDisableAutoSave:SaveGame"sv);
		REX::Assert(DisableAutoSave != nullptr);
		return *DisableAutoSave;
	}

	auto BGSSaveLoadManager::GetDisableAutoSave() -> bool
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

	auto BGSSaveLoadManager::GetAutoSavingMessageSetting() -> Setting&
	{
		static auto* AutoSaving = GetGameSetting("sAutoSaving"sv);
		REX::Assert(AutoSaving != nullptr);
		return *AutoSaving;
	}

	auto BGSSaveLoadManager::GetCannotSaveMessageSetting() -> Setting&
	{
		static auto* CannotSaveNow = GetGameSetting("sCantSaveNow"sv);
		REX::Assert(CannotSaveNow != nullptr);
		return *CannotSaveNow;
	}

	auto BGSSaveLoadManager::GetQuicksaveMessageSetting() -> Setting&
	{
		static auto* QuickSaving = GetGameSetting("sQuickSaving"sv);
		REX::Assert(QuickSaving != nullptr);
		return *QuickSaving;
	}

	auto BGSSaveLoadManager::GetSaveMessageSetting() -> Setting&
	{
		static auto* MenuDisplayShortXBoxSaveMessage = GetGameSetting("sMenuDisplayShortXBoxSaveMessage"sv);
		REX::Assert(MenuDisplayShortXBoxSaveMessage != nullptr);
		return *MenuDisplayShortXBoxSaveMessage;
	}

	auto BGSSaveLoadManager::GetSaveFailedMessageSetting() -> Setting&
	{
		static auto* SaveFailed = GetGameSetting("sSaveFailed"sv);
		REX::Assert(SaveFailed != nullptr);
		return *SaveFailed;
	}

	auto BGSSaveLoadManager::GetAutosaveMessage() -> BSFixedStringCS
	{
		const auto& setting = GetAutoSavingMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto BGSSaveLoadManager::GetCannotSaveMessage() -> BSFixedStringCS
	{
		const auto& setting = GetCannotSaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto BGSSaveLoadManager::GetQuicksaveMessage() -> BSFixedStringCS
	{
		const auto& setting = GetQuicksaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto BGSSaveLoadManager::GetSaveMessage() -> BSFixedStringCS
	{
		const auto& setting = GetSaveMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	auto BGSSaveLoadManager::GetSaveFailedMessage() -> BSFixedStringCS
	{
		const auto& setting = GetSaveFailedMessageSetting();
		if (!setting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return {};
		}

		return {setting.GetString()};
	}

	void BGSSaveLoadManager::AutosaveImpl(bool a_background)
	{
		using FuncType = decltype(&BGSSaveLoadManager::AutosaveImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::AutosaveImpl);
		std::invoke(FUNC, this, a_background);
	}

	void BGSSaveLoadManager::DeleteSaveFileImpl(
		const char* a_fileName,
		std::int32_t a_deviceID,
		bool a_checkHasSaveData)
	{
		using FuncType = decltype(&BGSSaveLoadManager::DeleteSaveFileImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::DeleteSaveFileImpl);
		std::invoke(FUNC, this, a_fileName, a_deviceID, a_checkHasSaveData);
	}

	void BGSSaveLoadManager::GenerateSaveFileNameImpl(
		char* a_saveFileName,
		bool a_displayOnly,
		SAVEFILE_CATEGORY a_saveCategory)
	{
		using FuncType = decltype(&BGSSaveLoadManager::GenerateSaveFileNameImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::GenerateSaveFileNameImpl);
		std::invoke(FUNC, this, a_saveFileName, a_displayOnly, a_saveCategory);
	}

	auto BGSSaveLoadManager::LoadGameImpl(
		const char* a_fileName,
		std::int32_t a_deviceID,
		std::uint32_t a_outputStats,
		bool a_checkForMods,
		bool a_ignoreMissingContent) -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::LoadGameImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::LoadGameImpl);
		return std::invoke(FUNC, this, a_fileName, a_deviceID, a_outputStats, a_checkForMods, a_ignoreMissingContent);
	}

	auto BGSSaveLoadManager::SaveGameImpl(
		const char* a_fileName,
		std::int32_t a_deviceID,
		std::uint32_t a_outputStats,
		bool a_compress) -> bool
	{
		using FuncType = decltype(&BGSSaveLoadManager::SaveGameImpl);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadManager::SaveGameImpl);
		return std::invoke(FUNC, this, a_fileName, a_deviceID, a_outputStats, a_compress);
	}
}

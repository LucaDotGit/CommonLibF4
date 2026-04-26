#include "RE/T/TESDataHandler.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/F/FormType.hpp"
#include "RE/T/TESFile.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	TESDataHandler* TESDataHandler::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<TESDataHandler**>{ ID::TESDataHandler::Singleton };
		return *SINGLETON;
	}

	bool TESDataHandler::AddFormToDataHandler(TESForm* a_form)
	{
		using FuncType = decltype(&TESDataHandler::AddFormToDataHandler);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDataHandler::AddFormToDataHandler };
		return std::invoke(FUNC, this, a_form);
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(NEW_REFR_DATA& a_data)
	{
		using FuncType = decltype(&TESDataHandler::CreateReferenceAtLocation);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDataHandler::CreateReferenceAtLocation };
		return std::invoke(FUNC, this, a_data);
	}

	TESWorldSpace* TESDataHandler::GetExtCellDataFromFileByEditorID(const char* a_cellEditorID, std::int32_t& a_outX, std::int32_t& a_outY)
	{
		using FuncType = decltype(&TESDataHandler::GetExtCellDataFromFileByEditorID);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDataHandler::GetExtCellDataFromFileByEditorID };
		return std::invoke(FUNC, this, a_cellEditorID, a_outX, a_outY);
	}

	bool TESDataHandler::IsFormIDInUse(TESFormID a_formID) const
	{
		using FuncType = decltype(&TESDataHandler::IsFormIDInUse);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDataHandler::IsFormIDInUse };
		return std::invoke(FUNC, this, a_formID);
	}

	bool TESDataHandler::CheckModsLoaded(bool a_everModded) const
	{
		using FuncType = decltype(&TESDataHandler::CheckModsLoaded);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDataHandler::CheckModsLoaded };
		return std::invoke(FUNC, this, a_everModded);
	}

	bool TESDataHandler::IsFileLoaded(std::string_view a_fileName) const
	{
		if (a_fileName.empty()) {
			return false;
		}

		const auto* file = FindLoadedFileByName(a_fileName);
		return file != nullptr;
	}

	std::uint32_t TESDataHandler::GetFileCount() const
	{
		auto fileCount = 0ui32;
		ForEachFile([&fileCount](TESFile* a_plugin) {
			if (a_plugin) {
				fileCount++;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return fileCount;
	}

	std::uint32_t TESDataHandler::GetLoadedFileCount() const
	{
		auto loadedFileCount = 0ui32;
		ForEachFile([&loadedFileCount](TESFile* a_plugin) {
			if (a_plugin && a_plugin->IsActive()) {
				loadedFileCount++;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return loadedFileCount;
	}

	std::uint32_t TESDataHandler::GetTotalFormCount() const
	{
		auto totalFormCount = 0ui32;
		ForEachFile([&totalFormCount](TESFile* a_plugin) {
			if (a_plugin) {
				totalFormCount += a_plugin->fileHeaderInfo.formCount;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return totalFormCount;
	}

	std::uint32_t TESDataHandler::GetTotalLoadedFormCount() const
	{
		auto totalLoadedFormCount = 0ui32;
		ForEachFile([&totalLoadedFormCount](TESFile* a_plugin) {
			if (a_plugin && a_plugin->IsActive()) {
				totalLoadedFormCount += a_plugin->fileHeaderInfo.formCount;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return totalLoadedFormCount;
	}

	BSTArray<TESForm*>& TESDataHandler::GetFormArray(FormType a_formType) noexcept
	{
		REX::Assert(a_formType >= FormType::kNone && a_formType < FormType::kTotal);
		return formArrays[std::to_underlying(a_formType)];
	}

	const BSTArray<TESForm*>& TESDataHandler::GetFormArray(FormType a_formType) const noexcept
	{
		REX::Assert(a_formType >= FormType::kNone && a_formType < FormType::kTotal);
		return formArrays[std::to_underlying(a_formType)];
	}

	TESFormID TESDataHandler::GetLocalFormID(TESFormID a_formID) noexcept
	{
		if (a_formID == EMPTY_FORM_ID) {
			return EMPTY_FORM_ID;
		}

		if (a_formID > EMPTY_RUNTIME_FORM_ID) {
			return a_formID;
		}

		if (a_formID > LIGHT_LOCAL_FORM_ID_MASK) {
			return a_formID & LIGHT_LOCAL_FORM_ID_MASK;
		}

		return a_formID & LOCAL_FORM_ID_MASK;
	}

	auto TESDataHandler::FindFormID(TESFormID a_localFormID, std::string_view a_fileName) const -> std::optional<TESFormID>
	{
		if (a_localFormID == EMPTY_FORM_ID) {
			return EMPTY_FORM_ID;
		}

		if (a_localFormID > EMPTY_RUNTIME_FORM_ID && a_fileName.empty()) {
			return a_localFormID;
		}

		const auto* file = FindLoadedFileByName(a_fileName);
		if (!file) {
			return std::nullopt;
		}

		if (file->IsLight()) {
			const auto lightPluginIndex = file->smallFileCompileIndex << LIGHT_FORM_INDEX_SHIFT;
			const auto lightLocalFormID = a_localFormID & LIGHT_LOCAL_FORM_ID_MASK;
			return EMPTY_LIGHT_FORM_ID | lightPluginIndex | lightLocalFormID;
		}

		const auto pluginIndex = file->compileIndex << FORM_INDEX_SHIFT;
		const auto localFormID = a_localFormID & LOCAL_FORM_ID_MASK;
		return EMPTY_FORM_ID | pluginIndex | localFormID;
	}

	auto TESDataHandler::FindForm(TESFormID a_localFormID, std::string_view a_fileName) const -> TESForm*
	{
		const auto formID = FindFormID(a_localFormID, a_fileName);
		if (!formID) {
			return nullptr;
		}

		return TESForm::FindFormByNumericID(*formID);
	}

	auto TESDataHandler::FindFormOrRef(TESFormID a_localFormID, std::string_view a_fileName) const -> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>
	{
		const auto formID = FindFormID(a_localFormID, a_fileName);
		if (!formID) {
			return std::nullopt;
		}

		return TESObjectREFR::FindFormOrRefByNumericID(*formID);
	}

	TESFile* TESDataHandler::FindFileByName(std::string_view a_fileName) const
	{
		if (a_fileName.empty()) {
			return nullptr;
		}

		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_fileName](TESFile* a_file) {
			if (!a_file) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			const auto fileName = std::string_view(a_file->filename.data());
			if (REX::EqualsIgnoreCase(a_fileName, fileName)) {
				result = a_file;
				return RE::BSContainer::ForEachResult::kStop;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	TESFile* TESDataHandler::FindFileByFormID(TESFormID a_formID) const
	{
		if (a_formID == EMPTY_FORM_ID) {
			return nullptr;
		}

		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_formID](TESFile* a_file) {
			if (!a_file) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			if (a_file->IsFormInFile(a_formID)) {
				result = a_file;
				return RE::BSContainer::ForEachResult::kStop;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	TESFile* TESDataHandler::FindFileByIndex(std::uint16_t a_index) const
	{
		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_index](TESFile* a_file) {
			if (!a_file) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			if (a_file->IsLight()) {
				if (a_file->smallFileCompileIndex == a_index) {
					result = a_file;
					return RE::BSContainer::ForEachResult::kStop;
				}
			}
			else {
				if (a_file->compileIndex == a_index) {
					result = a_file;
					return RE::BSContainer::ForEachResult::kStop;
				}
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	TESFile* TESDataHandler::FindLoadedFileByName(std::string_view a_fileName) const
	{
		if (a_fileName.empty()) {
			return nullptr;
		}

		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_fileName](TESFile* a_file) {
			if (!a_file || !a_file->IsActive()) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			const auto fileName = std::string_view(a_file->filename.data());
			if (REX::EqualsIgnoreCase(a_fileName, fileName)) {
				result = a_file;
				return RE::BSContainer::ForEachResult::kStop;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	TESFile* TESDataHandler::FindLoadedFileByFormID(TESFormID a_formID) const
	{
		if (a_formID == EMPTY_FORM_ID) {
			return nullptr;
		}

		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_formID](TESFile* a_file) {
			if (!a_file || !a_file->IsActive()) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			if (a_file->IsFormInFile(a_formID)) {
				result = a_file;
				return RE::BSContainer::ForEachResult::kStop;
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	TESFile* TESDataHandler::FindLoadedFileByIndex(std::uint16_t a_index) const
	{
		auto* result = static_cast<TESFile*>(nullptr);
		ForEachFile([&result, a_index](TESFile* a_file) {
			if (!a_file || !a_file->IsActive()) {
				return RE::BSContainer::ForEachResult::kContinue;
			}

			if (a_file->IsLight()) {
				if (a_file->smallFileCompileIndex == a_index) {
					result = a_file;
					return RE::BSContainer::ForEachResult::kStop;
				}
			}
			else {
				if (a_file->compileIndex == a_index) {
					result = a_file;
					return RE::BSContainer::ForEachResult::kStop;
				}
			}

			return RE::BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	auto TESDataHandler::FindFileIndex(std::string_view a_fileName) const -> std::optional<std::uint16_t>
	{
		const auto* file = FindFileByName(a_fileName);
		if (!file) {
			return std::nullopt;
		}

		if (file->IsLight()) {
			return file->smallFileCompileIndex;
		}

		return file->compileIndex;
	}

	auto TESDataHandler::FindLoadedFileIndex(std::string_view a_fileName) const -> std::optional<std::uint16_t>
	{
		const auto* file = FindLoadedFileByName(a_fileName);
		if (!file) {
			return std::nullopt;
		}

		if (file->IsLight()) {
			return file->smallFileCompileIndex;
		}

		return file->compileIndex;
	}

	TESDataHandler::RuntimeData& TESDataHandler::GetRuntimeData() noexcept
	{
		return REL::GetMemberAt<RuntimeData>(Offset::TESDataHandler::RuntimeData, this);
	}

	const TESDataHandler::RuntimeData& TESDataHandler::GetRuntimeData() const noexcept
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::TESDataHandler::RuntimeData, this);
	}

	TESDataHandler::VRModData* TESDataHandler::GetVRModData() noexcept
	{
		if (!F4SE::IsRuntimeOnlyVR()) {
			return nullptr;
		}

		return std::addressof(REL::GetMemberAt<VRModData>(Offset::TESDataHandler::VRModData, this));
	}

	const TESDataHandler::VRModData* TESDataHandler::GetVRModData() const noexcept
	{
		if (!F4SE::IsRuntimeOnlyVR()) {
			return nullptr;
		}

		return std::addressof(REL::GetMemberAt<const VRModData>(Offset::TESDataHandler::VRModData, this));
	}

	TESRegionDataManager* TESDataHandler::GetRegionDataManager() noexcept
	{
		return REL::GetMemberAt<TESRegionDataManager*>(Offset::TESDataHandler::RegionDataManager, this);
	}

	const TESRegionDataManager* TESDataHandler::GetRegionDataManager() const noexcept
	{
		return REL::GetMemberAt<const TESRegionDataManager*>(Offset::TESDataHandler::RegionDataManager, this);
	}

	BSContainer::ForEachResult TESDataHandler::ForEachFile(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESFile*)>>& a_predicate) const
	{
#if COMMONLIB_RUNTIME_VR == 0
		if (!F4SE::IsRuntimeOnlyVR()) {
			return compiledFileCollection.ForEachFile(a_predicate);
		}
#endif

		for (auto* file : files) {
			if (std::invoke(*a_predicate, file) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}

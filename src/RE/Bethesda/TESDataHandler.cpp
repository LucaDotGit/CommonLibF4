#include "RE/Bethesda/TESDataHandler.hpp"

namespace RE
{
	TESDataHandler* TESDataHandler::GetSingleton(bool a_VRESL)
	{
		static REL::Relocation<TESDataHandler**> singleton{ REL::RelocationID(711558, 2688883) };
		if (REL::Module::IsVR() && a_VRESL && !VRcompiledFileCollection) {
			const auto VRhandle = REX::W32::GetModuleHandleW(L"falloutvresl");
			if (VRhandle != NULL) {
				const auto GetCompiledFileCollection = reinterpret_cast<const TESFileCollection* (*)()>(REX::W32::GetProcAddress(VRhandle, "GetCompiledFileCollectionExtern"));
				if (GetCompiledFileCollection != nullptr) {
					TESDataHandler::VRcompiledFileCollection = const_cast<TESFileCollection*>(GetCompiledFileCollection());
				}
			}
		}
		return *singleton;
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(NEW_REFR_DATA& a_data)
	{
		using func_t = decltype(&TESDataHandler::CreateReferenceAtLocation);
		static REL::Relocation<func_t> func{ REL::RelocationID(500304, 500304) };
		return func(this, a_data);
	}

	bool TESDataHandler::AddFormToDataHandler(TESForm* a_form)
	{
		using func_t = decltype(&TESDataHandler::AddFormToDataHandler);
		static REL::Relocation<func_t> func{ REL::RelocationID(350112, 2192271) };
		return func(this, a_form);
	}

	bool TESDataHandler::CheckModsLoaded(bool a_everModded) const
	{
		using func_t = decltype(&TESDataHandler::CheckModsLoaded);
		static REL::Relocation<func_t> func{ REL::RelocationID(1432894, 2192323) };
		return func(this, a_everModded);
	}

	bool TESDataHandler::IsFormIDInUse(std::uint32_t a_formID) const
	{
		using func_t = decltype(&TESDataHandler::IsFormIDInUse);
		static REL::Relocation<func_t> func{ REL::RelocationID(1448838, 2192351) };
		return func(this, a_formID);
	}

	TESFormID TESDataHandler::LookupFormID(TESFormID a_rawFormID, std::string_view a_modName) const
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->compileIndex == 0xFF) {
			return 0;
		}

		if (REL::Module::IsVR() && !VRcompiledFileCollection) {
			// Use FalloutVR lookup logic, ignore light plugin index which doesn't exist in VR
			return (a_rawFormID & 0xFFFFFF) | (file->compileIndex << 24);
		}
		else {
			TESFormID formID = file->compileIndex << 24;
			formID += file->smallFileCompileIndex << 12;
			formID += a_rawFormID;
			return formID;
		}
	}

	TESForm* TESDataHandler::LookupForm(TESFormID a_rawFormID, std::string_view a_modName) const
	{
		auto file = LookupLoadedFile(a_modName);
		if (!file.first) {
			return nullptr;
		}

		TESFormID formID = 0;
		if (file.second) {
			formID = file.first->compileIndex << 24;
			formID += (a_rawFormID & 0x00FFFFFF);
		}
		else {
			formID = 0xFE000000;
			formID += file.first->smallFileCompileIndex << 12;
			formID += (a_rawFormID & 0x00000FFF);
		}

		return TESForm::GetFormByID(formID);
	}

	const std::pair<TESFile*, bool> TESDataHandler::LookupLoadedFile(std::string_view a_fileName) const
	{
		if (auto fullFile = LookupLoadedModByName(a_fileName))
			return { const_cast<TESFile*>(fullFile), true };
		if (auto smallFile = LookupLoadedLightModByName(a_fileName))
			return { const_cast<TESFile*>(smallFile), false };
		return { nullptr, false };
	}

	const TESFile* TESDataHandler::LookupModByName(std::string_view a_modName) const
	{
		for (auto& file : files) {
			if (a_modName.size() == strlen(file->filename) &&
				_strnicmp(file->filename, a_modName.data(), a_modName.size()) == 0) {
				return file;
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedModByName(std::string_view a_modName) const
	{
		auto pCompiledFileCollection = GetCompiledFileCollection();
		if (pCompiledFileCollection) {
			for (auto& file : pCompiledFileCollection->files) {
				if (a_modName.size() == strlen(file->filename) &&
					_strnicmp(file->filename, a_modName.data(), a_modName.size()) == 0) {
					return file;
				}
			}
		}
		else if (auto pLoadedMods = GetVRModData()) { // In VR so only have files loadedMods
			for (uint32_t i = 0; i < pLoadedMods->loadedModCount; i++) {
				auto& file = pLoadedMods->loadedMods[i];
				if (a_modName.size() == strlen(file->filename) &&
					_strnicmp(file->filename, a_modName.data(), a_modName.size()) == 0) {
					return file;
				}
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedLightModByName(std::string_view a_modName) const
	{
		auto pCompiledFileCollection = GetCompiledFileCollection();
		if (pCompiledFileCollection) {
			for (auto& smallFile : pCompiledFileCollection->smallFiles) {
				if (a_modName.size() == strlen(smallFile->filename) &&
					_strnicmp(smallFile->filename, a_modName.data(), a_modName.size()) == 0) {
					return smallFile;
				}
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedModByIndex(std::uint8_t a_index) const
	{
		auto pCompiledFileCollection = GetCompiledFileCollection();
		if (pCompiledFileCollection) {
			for (auto& file : pCompiledFileCollection->files) {
				if (file->compileIndex == a_index) {
					return file;
				}
			}
		}
		else if (auto pLoadedMods = GetVRModData()) { // In VR so only have files loadedMods
			for (uint32_t i = 0; i < pLoadedMods->loadedModCount; i++) {
				auto& file = pLoadedMods->loadedMods[i];
				if (file->compileIndex == a_index) {
					return file;
				}
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedLightModByIndex(std::uint16_t a_index) const
	{
		auto pCompiledFileCollection = GetCompiledFileCollection();
		if (pCompiledFileCollection) {
			for (auto& smallFile : pCompiledFileCollection->smallFiles) {
				if (smallFile->smallFileCompileIndex == a_index) {
					return smallFile;
				}
			}
		}
		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetModIndex(std::string_view a_modName) const
	{
		auto mod = LookupModByName(a_modName);
		return mod ? std::make_optional(mod->compileIndex) : std::nullopt;
	}

	std::optional<std::uint8_t> TESDataHandler::GetLoadedModIndex(std::string_view a_modName) const
	{
		auto mod = LookupLoadedModByName(a_modName);
		return mod ? std::make_optional(mod->compileIndex) : std::nullopt;
	}

	std::optional<std::uint16_t> TESDataHandler::GetLoadedLightModIndex(std::string_view a_modName) const
	{
		auto mod = LookupLoadedLightModByName(a_modName);
		return mod ? std::make_optional(mod->smallFileCompileIndex) : std::nullopt;
	}
}

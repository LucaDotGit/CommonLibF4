#include "RE/T/TESForm.hpp"

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/F/FORM_ENUM_STRING.hpp"
#include "RE/F/FormFlags.hpp"
#include "RE/T/TESDataHandler.hpp"
#include "RE/T/TESFileArray.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	std::int32_t TESForm::FormSortFunc::operator()(const TESForm* a_lhs, const TESForm* a_rhs) const noexcept
	{
		if (!a_lhs && !a_rhs) {
			return 0;
		}

		if (!a_lhs) {
			return -1;
		}

		if (!a_rhs) {
			return 1;
		}

		const auto leftTypeString = a_lhs->GetFormTypeString();
		const auto rightTypeString = a_rhs->GetFormTypeString();

		return REX::GetNumericStrongOrdering(REX::CompareIgnoreCase(leftTypeString, rightTypeString));
	}

	void TESForm::AddCompileIndex(std::uint32_t& a_id, TESFile* a_file)
	{
		using FuncType = decltype(&TESForm::AddCompileIndex);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESForm::AddCompileIndex };
		std::invoke(FUNC, a_id, a_file);
	}

	std::uint32_t& TESForm::GetTotalFormCount()
	{
		static const auto TOTAL_FORM_COUNT = REL::Relocation<std::uint32_t*>{ ID::TESForm::TotalFormCount };
		return *TOTAL_FORM_COUNT;
	}

	auto TESForm::GetAllFormsByEditorID()
		-> std::pair<BSTHashMap<BSFixedString, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>
	{
		static const auto FORM_MAP = REL::Relocation<BSTHashMap<BSFixedString, TESForm*>**>{ ID::TESForm::FormEditorIDMap };
		static const auto FORM_MAP_LOCK = REL::Relocation<BSReadWriteLock*>{ ID::TESForm::FormEditorIDMapLock };
		return std::make_pair(*FORM_MAP, std::ref(*FORM_MAP_LOCK));
	}

	auto TESForm::GetAllFormsByID()
		-> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>
	{
		return GetAllFormsByNumericID();
	}

	auto TESForm::GetAllFormsByNumericID()
		-> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>
	{
		static const auto FORM_MAP = REL::Relocation<BSTHashMap<TESFormID, TESForm*>**>{ ID::TESForm::FormNumericIDMap };
		static const auto FORM_MAP_LOCK = REL::Relocation<BSReadWriteLock*>{ ID::TESForm::FormNumericIDMapLock };
		return std::make_pair(*FORM_MAP, std::ref(*FORM_MAP_LOCK));
	}

	TESFile* TESForm::GetFile(std::int32_t a_index) const
	{
		const auto* files = sourceFiles.array;
		if (!files || files->empty()) {
			if (!IsPlayer() && !IsPlayerRef()) {
				return nullptr;
			}

			const auto* dataHandler = TESDataHandler::GetSingleton();
			return dataHandler ? dataHandler->FindLoadedFileByIndex(0) : nullptr;
		}

		if (a_index < 0 || static_cast<std::uint32_t>(a_index) >= files->size()) {
			return files->back();
		}

		return (*files)[a_index];
	}

	TESForm* TESForm::FindFormByEditorID(const BSFixedString& a_editorID)
	{
		if (a_editorID.empty()) {
			return nullptr;
		}

		const auto&& [editorIDMap, editorIDMutex] = GetAllFormsByEditorID();
		if (!editorIDMap) {
			return nullptr;
		}

		const auto editorIDLock = BSAutoReadLock(editorIDMutex);

		const auto formIt = editorIDMap->find(a_editorID);
		if (formIt == editorIDMap->end()) {
			return nullptr;
		}

		return formIt->second;
	}

	TESForm* TESForm::FindFormByID(TESFormID a_formID)
	{
		return FindFormByNumericID(a_formID);
	}

	TESForm* TESForm::FindFormByNumericID(TESFormID a_formID)
	{
		if (a_formID == 0) {
			return nullptr;
		}

		const auto&& [formIDMap, formIDMutex] = GetAllFormsByNumericID();
		if (!formIDMap) {
			return nullptr;
		}

		const auto formIDLock = BSAutoReadLock(formIDMutex);

		const auto formIt = formIDMap->find(a_formID);
		if (formIt == formIDMap->end()) {
			return nullptr;
		}

		return formIt->second;
	}

	auto TESForm::GetEditorIDByForm(const TESForm* a_form)
		-> std::optional<BSFixedString>
	{
		if (!a_form) {
			return std::nullopt;
		}

		// `GetFormEditorID` returns only a raw pointer,
		// so in case the editor ID gets deleted while assigning it to a `BSFixedString`,
		// the editor ID map mutex needs to be locked while copying the ID.

		const auto&& [editorIdMap, editorIdMutex] = GetAllFormsByEditorID();
		if (!editorIdMap) {
			return std::nullopt;
		}

		const auto editorIDLock = BSAutoReadLock(editorIdMutex);
		return a_form->GetFormEditorID();
	}

	std::string_view TESForm::GetFormTypeString() const
	{
		return FORM_ENUM_STRING::GetFormStringByType(GetFormType());
	}

	FormFlags TESForm::GetFormFlags() const noexcept
	{
		return *formFlags;
	}

	TESFormID TESForm::GetFormID() const noexcept
	{
		return formID;
	}

	FormType TESForm::GetFormType() const noexcept
	{
		return *formType;
	}

	TESFormID TESForm::GetLocalFormID() const
	{
		return TESDataHandler::GetLocalFormID(GetFormID());
	}

	bool TESForm::IsAlchemyItem() const noexcept
	{
		return Is(FormType::kPotion);
	}

	bool TESForm::IsCreated() const noexcept
	{
		return formID > 0xFF000000;
	}

	bool TESForm::IsDeleted() const noexcept
	{
		return formFlags.any(FormFlags::kDeleted);
	}

	bool TESForm::IsDisabled() const noexcept
	{
		return formFlags.any(FormFlags::kDisabled);
	}

	bool TESForm::IsInitialized() const noexcept
	{
		return formFlags.any(FormFlags::kInitialized);
	}

	bool TESForm::IsPlayer() const noexcept
	{
		return GetFormID() == PLAYER_BASE_FORM_ID;
	}

	bool TESForm::IsPlayerRef() const noexcept
	{
		return GetFormID() == PLAYER_REF_FORM_ID;
	}

	bool TESForm::IsWeapon() const noexcept
	{
		return Is(FormType::kWeapon);
	}

	void TESForm::SetInGameFormFlags(InGameFormFlags a_flags, bool a_value)
	{
		inGameFormFlags.set(a_value, a_flags);
		AddChange(ChangeFlags::kFlags);
	}

	void TESForm::SetTemporary()
	{
		using FuncType = decltype(&TESForm::SetTemporary);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESForm::SetTemporary };
		std::invoke(FUNC, this);
	}

	bool TESForm::CanHoldKeywords(const TESForm* a_form)
	{
		if (!a_form) {
			return false;
		}

		return (DynamicCast<const BGSKeywordForm*>(a_form) != nullptr) ||
			   (DynamicCast<const TESObjectREFR*>(a_form) != nullptr);
	}

	auto TESForm::ContainsKeyword(const TESForm* a_form, const BGSKeyword* a_keyword)
		-> std::optional<bool>
	{
		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->ContainsKeyword(a_keyword);
	}

	auto TESForm::GetKeywordCount(const TESForm* a_form)
		-> std::optional<std::uint32_t>
	{
		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::GetKeywordCount(ref);
		}

		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->numKeywords;
	}

	auto TESForm::GetKeywordIndex(const TESForm* a_form, const BGSKeyword* a_keyword)
		-> std::optional<std::uint32_t>
	{
		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::GetKeywordIndex(ref, a_keyword);
		}

		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->GetKeywordIndex(a_keyword);
	}

	auto TESForm::GetKeywords(const TESForm* a_form)
		-> std::optional<std::vector<BGSKeyword*>>
	{
		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::GetKeywords(ref);
		}

		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		const auto keywords = keywordForm->GetKeywords();
		return std::vector<BGSKeyword*>{ keywords.begin(), keywords.end() };
	}

	auto TESForm::SetKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			TESObjectREFR::SetKeywords(ref, a_keywords);
			return true;
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		keywordForm->SetKeywords(a_keywords);
		return true;
	}

	auto TESForm::GetNthKeyword(const TESForm* a_form, std::uint32_t a_index)
		-> std::optional<BGSKeyword*>
	{
		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::GetNthKeyword(ref, a_index);
		}

		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->GetNthKeyword(a_index);
	}

	auto TESForm::SetNthKeyword(TESForm* a_form, std::uint32_t a_index, BGSKeyword* a_keyword)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::SetNthKeyword(ref, a_index, a_keyword);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->SetNthKeyword(a_index, a_keyword);
	}

	auto TESForm::RemoveNthKeyword(TESForm* a_form, std::uint32_t a_index)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::RemoveNthKeyword(ref, a_index);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->RemoveNthKeyword(a_index);
	}

	auto TESForm::AddKeyword(TESForm* a_form, BGSKeyword* a_keyword)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::AddKeyword(ref, a_keyword);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->AddKeyword(a_keyword);
	}

	auto TESForm::RemoveKeyword(TESForm* a_form, BGSKeyword* a_keyword)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::RemoveKeyword(ref, a_keyword);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->RemoveKeyword(a_keyword);
	}

	auto TESForm::ReplaceKeyword(TESForm* a_form, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword)
		-> std::optional<bool>
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::ReplaceKeyword(ref, a_oldKeyword, a_newKeyword);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return std::nullopt;
		}

		return keywordForm->ReplaceKeyword(a_oldKeyword, a_newKeyword);
	}

	bool TESForm::AddKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords)
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::AddKeywords(ref, a_keywords);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		return keywordForm ? keywordForm->AddKeywords(a_keywords) : false;
	}

	bool TESForm::RemoveKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords)
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::RemoveKeywords(ref, a_keywords);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		return keywordForm ? keywordForm->RemoveKeywords(a_keywords) : false;
	}

	bool TESForm::ClearKeywords(TESForm* a_form)
	{
		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::ClearKeywords(ref);
		}

		auto* keywordForm = DynamicCast<BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return false;
		}

		keywordForm->ClearKeywords();
		return true;
	}

	BSContainer::ForEachResult TESForm::ForEachKeyword(const TESForm* a_form,
		const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate)
	{
		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (ref) {
			return TESObjectREFR::ForEachKeyword(ref, a_predicate);
		}

		const auto* keywordForm = DynamicCast<const BGSKeywordForm*>(a_form);
		if (!keywordForm) {
			return BSContainer::ForEachResult::kContinue;
		}

		return keywordForm->ForEachKeyword(a_predicate);
	}
}

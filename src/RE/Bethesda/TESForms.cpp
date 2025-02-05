#include "RE/Bethesda/TESForms.hpp"

#include "RE/Bethesda/BSExtraData.hpp"
#include "RE/Bethesda/TESObjectREFRs.hpp"
#include "RE/Bethesda/TESWaterForm.hpp"
#include "RE/Bethesda/TESWorldSpace.hpp"

namespace RE
{
	TESForm* TESForm::GetFormByID(TESFormID a_formID)
	{
		const auto& [map, lock] = GetAllForms();
		BSAutoReadLock l{ lock };
		if (map) {
			const auto it = map->find(a_formID);
			return it != map->end() ? it->second : nullptr;
		}
		else {
			return nullptr;
		}
	}

	TESForm* TESForm::GetFormByEditorID(const BSFixedString& a_editorID)
	{
		const auto& [map, lock] = GetAllFormsByEditorID();
		BSAutoReadLock l{ lock };
		if (map) {
			const auto it = map->find(a_editorID);
			return it != map->end() ? it->second : nullptr;
		}
		else {
			return nullptr;
		}
	}

	TESFormID TESForm::GetLocalFormID() const
	{
		auto file = GetFile(0);

		std::uint32_t fileIndex = file->compileIndex << (3 * 8);
		fileIndex += file->smallFileCompileIndex << ((1 * 8) + 4);

		return formID & ~fileIndex;
	}

	uint16_t BGSKeyword::GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type)
	{
		assert(a_type < KeywordType::kTotal);
		const auto keywords = GetTypedKeywords();
		if (keywords) {
			const auto& arr = (*keywords)[std::to_underlying(a_type)];
			for (uint16_t i = 0; i < arr.size(); ++i) {
				if (arr[i] == a_keyword) {
					return i;
				}
			}
		}
		return 0xFFFF;
	}

	BGSKeyword* BGSKeyword::GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index)
	{
		assert(a_type < KeywordType::kTotal);
		const auto keywords = GetTypedKeywords();
		if (keywords) {
			const auto& arr = (*keywords)[std::to_underlying(a_type)];
			return a_index < arr.size() ? arr[a_index] : nullptr;
		}
		else {
			return nullptr;
		}
	}

	auto BGSKeyword::GetTypedKeywords()
		-> std::optional<std::span<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::kTotal)>>
	{
		static REL::Relocation<BSTArray<BGSKeyword*>(*)[std::to_underlying(KeywordType::kTotal)]> keywords{ REL::ID(1095775) };
		if (*keywords) {
			return { *keywords };
		}
		else {
			return std::nullopt;
		}
	}

	bool BGSLocation::IsChild(const BGSLocation* a_possibleChild) const
	{
		if (!a_possibleChild) {
			return false;
		}

		for (auto it = a_possibleChild->parentLoc; it; it = it->parentLoc) {
			if (this == it) {
				return true;
			}
		}

		return false;
	}

	bool BGSLocation::IsParent(const BGSLocation* a_possibleParent) const
	{
		if (!a_possibleParent) {
			return false;
		}

		for (auto it = parentLoc; it; it = it->parentLoc) {
			if (a_possibleParent == it) {
				return true;
			}
		}

		return false;
	}

	BSContainer::ForEachResult TESObjectCELL::ForEachRef(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		const auto lock = BSSpinLock{ spinLock };

		for (const auto& ref : references) {
			if (ref && a_callback(ref.get()) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESObjectCELL::ForEachRefInRange(const NiPoint3& a_origin, float a_radius,
		std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (a_radius <= 0.0f) {
			return ForEachRef(a_callback);
		}

		const auto squaredRadius = a_radius * a_radius;

		return ForEachRef([&](TESObjectREFR* a_ref) {
			const auto distance = a_origin.GetSquaredDistance(a_ref->GetPosition());
			if (distance <= squaredRadius) {
				return a_callback(a_ref);
			}

			return BSContainer::ForEachResult::kContinue;
		});
	}

	TESWaterForm* TESObjectCELL::GetWaterType() const noexcept
	{
		const auto xWater = extraList ? extraList->GetByType<ExtraCellWaterType>() : nullptr;
		auto water = xWater ? xWater->water : nullptr;
		if (!water) {
			water = IsExterior() && worldSpace ? worldSpace->GetWaterType() : nullptr;
			if (!water) {
				water = TESWaterForm::GetDefaultWater();
			}
		}

		return water;
	}

	bool TESIdleForm::CheckConditions(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef, bool a_recurseUp) const
	{
		if (!conditions.IsTrue(a_actionRef, a_targetRef)) {
			return false;
		}
		if (a_recurseUp) {
			if (parentIdle) {
				return parentIdle->CheckConditions(a_actionRef, a_targetRef, a_recurseUp);
			}
		}
		return true;
	}

	BSContainer::ForEachResult BGSListForm::ForEachForm(std::function<BSContainer::ForEachResult(TESForm*)> a_callback) const
	{
		for (auto* form : arrayOfForms) {
			if (form && a_callback(form) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto [map, mutex] = TESForm::GetAllForms();
		const auto lock = BSAutoReadLock{ mutex };

		for (const auto ID : *scriptForms) {
			const auto it = map->find(ID);
			if (it != map->end()) {
				continue;
			}

			auto* form = it->second;
			if (form && a_callback(form) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	bool BGSListForm::Contains(const TESForm* a_form) const
	{
		if (!a_form) {
			return false;
		}

		for (const auto* form : arrayOfForms) {
			if (form == a_form) {
				return true;
			}
		}

		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		for (const auto ID : *scriptForms) {
			if (ID == a_form->formID) {
				return true;
			}
		}

		return false;
	}

	void BGSListForm::AddScriptForm(const TESForm* a_form)
	{
		if (!a_form) {
			return;
		}

		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			scriptForms = new BSTArray<TESFormID>();
		}

		scriptForms->push_back(a_form->formID);
		scriptAddedFormCount = scriptForms->size();

		AddChange(CHANGE_TYPE::kFormListAddedForm);
	}

	bool BGSListForm::RemoveScriptForm(const TESForm* a_form)
	{
		if (!a_form) {
			return false;
		}

		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		const auto it = std::ranges::find(*scriptForms, a_form->formID);
		if (it == scriptForms->end()) {
			return false;
		}

		scriptForms->erase(it);
		scriptAddedFormCount = scriptForms->size();

		AddChange(CHANGE_TYPE::kFormListAddedForm);
		return true;
	}
}

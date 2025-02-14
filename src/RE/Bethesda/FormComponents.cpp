#include "RE/Bethesda/FormComponents.hpp"

#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/FormUtil.hpp"
#include "RE/Bethesda/TESBoundAnimObjects.hpp"
#include "RE/Bethesda/TESForms.hpp"

namespace RE
{
	namespace detail
	{
		BGSKeyword* BGSKeywordGetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index)
		{
			return BGSKeyword::GetTypedKeywordByIndex(a_type, a_index);
		}

		std::uint16_t BGSKeywordGetIndexForTypedKeyword(BGSKeyword* a_keyword, KeywordType a_type)
		{
			return BGSKeyword::GetIndexForTypedKeyword(a_keyword, a_type);
		}
	}

	BSContainer::ForEachResult BGSKeywordForm::ForEachKeyword(std::function<BSContainer::ForEachResult(BGSKeyword*)> a_callback) const
	{
		if (!keywords) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numKeywords; i++) {
			if (keywords[i] && a_callback(keywords[i]) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	bool BGSKeywordForm::AddKeywords(const std::vector<BGSKeyword*>& a_keywords)
	{
		auto copiedData = std::vector<BGSKeyword*>{ keywords, keywords + numKeywords };
		std::ranges::remove_copy_if(a_keywords, std::back_inserter(copiedData), [&](auto& keyword) {
			return std::ranges::find(copiedData, keyword) != copiedData.end();
		});

		CopyKeywords(copiedData);
		return true;
	}

	bool BGSKeywordForm::RemoveKeywords(const std::vector<BGSKeyword*>& a_keywords)
	{
		auto copiedData = std::vector<BGSKeyword*>{ keywords, keywords + numKeywords };
		if (std::ranges::remove_if(copiedData, [&](auto& keyword) { return std::ranges::find(a_keywords, keyword) != a_keywords.end(); })) {
			CopyKeywords(copiedData);
			return true;
		}

		return false;
	}

	void BGSKeywordForm::CopyKeywords(const std::vector<BGSKeyword*>& a_copiedData)
	{
		const auto oldData = keywords;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<BGSKeyword*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numKeywords = static_cast<std::uint32_t>(newSize);
		keywords = newData;

		free(oldData);
	}

	void BGSKeywordForm::AddKeyword(BGSKeyword* a_keyword)
	{
		if (a_keyword && !HasKeyword(a_keyword)) {
			auto copiedData = std::vector<BGSKeyword*>{ keywords, keywords + numKeywords };
			copiedData.push_back(a_keyword);
			CopyKeywords(copiedData);
		}
	}

	bool BGSKeywordForm::RemoveKeyword(std::uint32_t a_index)
	{
		auto copiedData = std::vector<BGSKeyword*>{ keywords, keywords + numKeywords };
		copiedData.erase(copiedData.cbegin() + a_index);
		CopyKeywords(copiedData);
		return true;
	}

	bool BGSKeywordForm::RemoveKeyword(BGSKeyword* a_keyword)
	{
		const auto index = GetKeywordIndex(a_keyword);
		return index.has_value() && RemoveKeyword(*index);
	}

	bool BGSKeywordForm::ContainsKeywordString(std::string_view a_editorID) const
	{
		return ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID.contains(a_editorID)) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	bool BGSKeywordForm::HasKeywordString(std::string_view a_editorID) const
	{
		return ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID == a_editorID) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	bool BGSKeywordForm::HasKeywordID(TESFormID a_formID) const
	{
		return ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->GetFormID() == a_formID) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	BGSKeyword* BGSKeywordForm::GetKeywordAt(std::uint32_t a_index) const
	{
		return a_index < numKeywords ? keywords[a_index] : nullptr;
	}

	std::optional<std::uint32_t> BGSKeywordForm::GetKeywordIndex(BGSKeyword* a_keyword) const
	{
		if (!a_keyword) {
			return std::nullopt;
		}

		for (auto i = 0ui32; i < numKeywords; i++) {
			if (keywords[i] == a_keyword) {
				return i;
			}
		}

		return std::nullopt;
	}

	void TESContainer::ForEachContainerObject(std::function<bool(ContainerObject&)> a_fn) const
	{
		if (!containerObjects) {
			return;
		}

		for (auto i = 0ui32; i < numContainerObjects; i++) {
			if (const auto entry = containerObjects[i]; entry && !a_fn(*entry)) {
				break;
			}
		}
	}

	bool TESContainer::AddObject(TESBoundObject* a_object, std::int32_t a_count, TESForm* a_owner)
	{
		bool added = false;

		for (auto i = 0ui32; i < numContainerObjects; i++) {
			if (const auto entry = containerObjects[i]; entry && entry->obj == a_object) {
				entry->count += a_count;
				added = true;
				break;
			}
		}

		if (!added) {
			auto copiedData = std::vector<ContainerObject*>{ containerObjects, containerObjects + numContainerObjects };
			const auto newObj = new ContainerObject(a_object, a_count, a_owner);
			copiedData.push_back(newObj);
			CopyObjectList(copiedData);
			return true;
		}

		return added;
	}

	bool TESContainer::AddObjectsToContainer(std::map<TESBoundObject*, std::int32_t>& a_objects, TESForm* a_owner)
	{
		for (auto i = 0ui32; i < numContainerObjects; i++) {
			if (const auto entry = containerObjects[i]; entry && entry->obj) {
				if (auto it = a_objects.find(entry->obj); it != a_objects.end()) {
					entry->count += it->second;
					a_objects.erase(it);
				}
			}
		}

		if (!a_objects.empty()) {
			auto copiedData = std::vector<ContainerObject*>{ containerObjects, containerObjects + numContainerObjects };
			for (auto& [object, count] : a_objects) {
				const auto newObj = new ContainerObject(object, count, a_owner);
				copiedData.push_back(newObj);
			}
			CopyObjectList(copiedData);
		}

		return true;
	}

	void TESContainer::CopyObjectList(const std::vector<ContainerObject*>& a_copiedData)
	{
		const auto oldData = containerObjects;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<ContainerObject*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numContainerObjects = static_cast<std::uint32_t>(newSize);
		containerObjects = newData;

		free(oldData);
	}

	std::optional<BGSLocalizedString> TESFullName::GetFullName(const TESForm* a_form, bool a_strict)
	{
		const auto* nameForm = a_form->As<TESFullName>();
		if (nameForm) {
			return nameForm->fullName;
		}

		if (a_strict) {
			switch (a_form->GetFormType()) {
				case ENUM_FORMTYPE::kKYWD: // BGSKeyword
				case ENUM_FORMTYPE::kLCRT: // BGSLocationRefType
				case ENUM_FORMTYPE::kAACT: // BGSAction
				case ENUM_FORMTYPE::kLIGH: // TESObjectLIGH
				case ENUM_FORMTYPE::kSTAT: // TESObjectSTAT
				case ENUM_FORMTYPE::kSCOL: // BGSStaticCollection
				case ENUM_FORMTYPE::kMSTT: // BGSMovableStatic
				case ENUM_FORMTYPE::kFLST: // BGSListForm
					break;
				default:
					return std::nullopt;
			}
		}

		const auto& map = GetSparseFullNameMap();
		const auto it = map.find(a_form);

		if (it != map.end()) {
			return it->second;
		}

		return std::nullopt;
	}

	bool TESFullName::SetFullName(TESForm* a_form, std::string_view a_fullName)
	{
		const auto nameForm = a_form->As<TESFullName>();
		if (!nameForm) {
			return false;
		}

		nameForm->fullName = a_fullName;
		if (a_form->Is<TESActorBase>()) {
			a_form->AddChange(CHANGE_TYPE::kActorBaseFullName);
		}
		else if (a_form->Is<TESObjectCELL>()) {
			a_form->AddChange(CHANGE_TYPE::kCellFullname);
		}
		else {
			a_form->AddChange(CHANGE_TYPE::kBaseObjectFullName);
		}

		return true;
	}

	std::optional<std::int32_t> TESValueForm::GetFormValue(const TESForm* a_form)
	{
		const auto valueForm = a_form->As<TESValueForm>();
		if (!valueForm) {
			return std::nullopt;
		}

		return valueForm->value;
	}

	bool TESValueForm::SetFormValue(TESForm* a_form, std::int32_t a_value)
	{
		const auto valueForm = a_form->As<TESValueForm>();
		if (!valueForm) {
			return false;
		}

		valueForm->value = a_value;
		a_form->AddChange(CHANGE_TYPE::kBaseObjectValue);
		return true;
	}

	bool TESSpellList::SpellData::HasSpell(const SpellItem* a_spell) const
	{
		return std::find(spells, spells + numSpells, a_spell) != spells + numSpells;
	}

	bool TESSpellList::SpellData::HasLevSpell(const TESLevSpell* a_levSpell) const
	{
		return std::find(levSpells, levSpells + numLevSpells, a_levSpell) != levSpells + numLevSpells;
	}

	std::optional<std::uint32_t> TESSpellList::SpellData::GetIndex(const SpellItem* a_spell) const
	{
		if (!spells) {
			return std::nullopt;
		}

		for (auto i = 0ui32; i < numSpells; i++) {
			if (spells[i] == a_spell) {
				return i;
			}
		}

		return std::nullopt;
	}

	std::optional<std::uint32_t> TESSpellList::SpellData::GetIndex(const TESLevSpell* a_levSpell) const
	{
		if (!levSpells) {
			return std::nullopt;
		}

		for (auto i = 0ui32; i < numLevSpells; i++) {
			if (levSpells[i] == a_levSpell) {
				return i;
			}
		}

		return std::nullopt;
	}

	bool TESSpellList::SpellData::AddLevSpells(const std::vector<TESLevSpell*>& a_levSpells)
	{
		auto copiedData = std::vector<TESLevSpell*>{ levSpells, levSpells + numLevSpells };
		std::ranges::remove_copy_if(a_levSpells, std::back_inserter(copiedData), [&](TESLevSpell* spell) {
			return std::ranges::find(copiedData, spell) != copiedData.end();
		});
		CopySpellList(copiedData);
		return true;
	}

	bool TESSpellList::SpellData::AddSpells(const std::vector<SpellItem*>& a_spells)
	{
		auto copiedData = std::vector<SpellItem*>{ spells, spells + numSpells };
		std::ranges::remove_copy_if(a_spells, std::back_inserter(copiedData), [&](SpellItem* spell) {
			return std::ranges::find(copiedData, spell) != copiedData.end();
		});
		CopySpellList(copiedData);
		return true;
	}

	bool TESSpellList::SpellData::RemoveLevSpells(const std::vector<TESLevSpell*>& a_levSpells)
	{
		auto copiedData = std::vector<TESLevSpell*>{ levSpells, levSpells + numLevSpells };
		if (std::ranges::remove_if(copiedData, [&](TESLevSpell* spell) { return std::ranges::find(a_levSpells, spell) != a_levSpells.end(); })) {
			CopySpellList(copiedData);
			return true;
		}
		return false;
	}

	bool TESSpellList::SpellData::RemoveSpells(const std::vector<SpellItem*>& a_spells)
	{
		auto copiedData = std::vector<SpellItem*>{ spells, spells + numSpells };
		if (std::ranges::remove_if(copiedData, [&](SpellItem* spell) { return std::ranges::find(a_spells, spell) != a_spells.end(); })) {
			CopySpellList(copiedData);
			return true;
		}
		return false;
	}

	void TESSpellList::SpellData::CopySpellList(const std::vector<TESLevSpell*>& a_copiedData)
	{
		const auto oldData = levSpells;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<TESLevSpell*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numLevSpells = static_cast<std::uint32_t>(newSize);
		levSpells = newData;

		free(oldData);
	}

	void TESSpellList::SpellData::CopySpellList(const std::vector<SpellItem*>& a_copiedData)
	{
		const auto oldData = spells;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<SpellItem*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numSpells = static_cast<std::uint32_t>(newSize);
		spells = newData;

		free(oldData);
	}

	bool TESSpellList::SpellData::AddLevSpell(TESLevSpell* a_levSpell)
	{
		if (a_levSpell && !HasLevSpell(a_levSpell)) {
			auto copiedData = std::vector<TESLevSpell*>{ levSpells, levSpells + numLevSpells };
			copiedData.push_back(a_levSpell);
			CopySpellList(copiedData);
			return true;
		}
		return false;
	}

	bool TESSpellList::SpellData::AddSpell(SpellItem* a_spell)
	{
		if (a_spell && !HasSpell(a_spell)) {
			auto copiedData = std::vector<SpellItem*>{ spells, spells + numSpells };
			copiedData.push_back(a_spell);
			CopySpellList(copiedData);
			return true;
		}

		return false;
	}

	bool TESSpellList::SpellData::RemoveLevSpell(TESLevSpell* a_levSpell)
	{
		auto copiedData = std::vector<TESLevSpell*>{ levSpells, levSpells + numLevSpells };
		if (std::ranges::remove(copiedData, a_levSpell)) {
			CopySpellList(copiedData);
			return true;
		}

		return false;
	}

	bool TESSpellList::SpellData::RemoveSpell(SpellItem* a_spell)
	{
		auto copiedData = std::vector<SpellItem*>{ spells, spells + numSpells };
		if (std::ranges::remove(copiedData, a_spell)) {
			CopySpellList(copiedData);
			return true;
		}

		return false;
	}
}

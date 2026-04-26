#include "RE/T/TESLeveledList.hpp"

#include "RE/B/BGSKeyword.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/L/LEVELED_OBJECT.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	auto TESLeveledList::GetSpecialChanceGlobalMap() -> BSTHashMap<TESLeveledList*, TESGlobal*>&
	{
		static const auto SPECIAL_CHANCE_GLOBAL_MAP = REL::Relocation<BSTHashMap<TESLeveledList*, TESGlobal*>*>{ ID::TESLeveledList::SpecialChanceGlobalMap, Offset::TESLeveledList::SpecialChanceGlobalMap };
		return *SPECIAL_CHANCE_GLOBAL_MAP;
	}

	void TESLeveledList::CalculateCurrentFormList(
		std::uint16_t a_level,
		std::uint16_t a_count,
		BSScrapArray<CALCED_OBJECT>& a_outCont,
		LeveledListAllBelowForce a_allBelowForce,
		bool a_clampToPlayer,
		INSTANCE_FILTER* a_instanceFilter,
		const char* a_overrideName)
	{
		using FuncType = decltype(&TESLeveledList::CalculateCurrentFormList);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESLeveledList::CalculateCurrentFormList };
		FUNC(this, a_level, a_count, a_outCont, a_allBelowForce, a_clampToPlayer, a_instanceFilter, a_overrideName);
	}

	void TESLeveledList::CalculateCurrentFormListForRef(TESObjectREFR* a_ref, BSScrapArray<CALCED_OBJECT>& a_outCont, bool a_legendary)
	{
		using FuncType = decltype(&TESLeveledList::CalculateCurrentFormListForRef);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESLeveledList::CalculateCurrentFormListForRef };
		FUNC(this, a_ref, a_outCont, a_legendary);
	}

	auto TESLeveledList::GetKeywordChances() const -> std::optional<std::vector<std::pair<BGSKeyword*, std::int32_t>>>
	{
		if (!keywordChances) {
			return std::nullopt;
		}

		auto result = std::vector<std::pair<BGSKeyword*, std::int32_t>>();
		result.reserve(keywordChances->size());

		for (const auto& [keywordForm, chance] : *keywordChances) {
			auto* keyword = DynamicCast<BGSKeyword*>(keywordForm);
			if (!keyword) {
				continue;
			}

			result.emplace_back(keyword, chance.int32);
		}

		return result;
	}

	void TESLeveledList::SetKeywordChances(std::span<const std::pair<BGSKeyword*, std::int32_t>> a_chances)
	{
		if (keywordChances) {
			delete keywordChances;
			keywordChances = nullptr;
		}

		if (a_chances.empty()) {
			return;
		}

		auto* newData = new BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>();
		newData->reserve(static_cast<std::uint32_t>(a_chances.size()));

		for (const auto& [keyword, chance] : a_chances) {
			newData->emplace_back(keyword, chance);
		}

		keywordChances = newData;
	}

	std::uint8_t TESLeveledList::GetLevObjectCount() const noexcept
	{
		return GetEditorLevObjectCount() + GetScriptLevObjectCount();
	}

	std::uint8_t TESLeveledList::GetEditorLevObjectCount() const noexcept
	{
		return baseListCount;
	}

	std::uint8_t TESLeveledList::GetScriptLevObjectCount() const noexcept
	{
		return scriptListCount;
	}

	std::span<LEVELED_OBJECT> TESLeveledList::GetEditorLevObjects() noexcept
	{
		return { leveledLists.data(), baseListCount };
	}

	std::span<LEVELED_OBJECT const> TESLeveledList::GetEditorLevObjects() const noexcept
	{
		return { leveledLists.data(), baseListCount };
	}

	void TESLeveledList::SetEditorLevObjects(std::span<LEVELED_OBJECT> a_objects)
	{
		ClearEditorLevObjects();

		if (a_objects.empty()) {
			return;
		}

		const auto newCount = static_cast<std::uint8_t>(std::min(a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < newCount; i++) {
			newData[i] = a_objects[i];
		}

		leveledLists = std::move(newData);
		baseListCount = newCount;
	}

	std::span<LEVELED_OBJECT*> TESLeveledList::GetScriptLevObjects() noexcept
	{
		return { scriptAddedLists.data(), scriptListCount };
	}

	std::span<LEVELED_OBJECT* const> TESLeveledList::GetScriptLevObjects() const noexcept
	{
		return { scriptAddedLists.data(), scriptListCount };
	}

	void TESLeveledList::SetScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects)
	{
		ClearScriptLevObjects();

		if (a_objects.empty()) {
			return;
		}

		const auto newCount = static_cast<std::uint8_t>(std::min(a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < newCount; i++) {
			newData[i] = a_objects[i].release();
		}

		scriptAddedLists = std::move(newData);
		scriptListCount = newCount;

		AddLevObjectsChange();
	}

	LEVELED_OBJECT* TESLeveledList::GetNthLevObject(std::uint8_t a_index) const
	{
		if (a_index < baseListCount) {
			return GetNthEditorLevObject(a_index);
		}

		return GetNthScriptLevObject(a_index - baseListCount);
	}

	bool TESLeveledList::SetNthLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object)
	{
		if (a_index < baseListCount) {
			return SetNthEditorLevObject(a_index, a_object);
		}

		return SetNthScriptLevObject(a_index - baseListCount, std::make_unique<LEVELED_OBJECT>(a_object));
	}

	bool TESLeveledList::RemoveNthLevObject(std::uint8_t a_index)
	{
		if (a_index < baseListCount) {
			return RemoveNthEditorLevObject(a_index);
		}

		return RemoveNthScriptLevObject(a_index - baseListCount);
	}

	LEVELED_OBJECT* TESLeveledList::GetNthEditorLevObject(std::uint8_t a_index) const
	{
		return a_index < baseListCount ? const_cast<LEVELED_OBJECT*>(std::addressof(leveledLists[a_index])) : nullptr;
	}

	bool TESLeveledList::SetNthEditorLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object)
	{
		if (a_index >= baseListCount) {
			return false;
		}

		leveledLists[a_index] = a_object;
		return true;
	}

	bool TESLeveledList::RemoveNthEditorLevObject(std::uint8_t a_index)
	{
		if (a_index >= baseListCount) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(baseListCount - 1);

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < a_index; i++) {
			newData[i] = leveledLists[i];
		}

		for (auto i = static_cast<std::uint8_t>(a_index + 1); i < baseListCount; i++) {
			newData[i - 1] = leveledLists[i];
		}

		leveledLists = std::move(newData);
		baseListCount = newCount;
		return true;
	}

	LEVELED_OBJECT* TESLeveledList::GetNthScriptLevObject(std::uint8_t a_index) const
	{
		return a_index < scriptListCount ? scriptAddedLists[a_index] : nullptr;
	}

	bool TESLeveledList::SetNthScriptLevObject(std::uint8_t a_index, std::unique_ptr<LEVELED_OBJECT> a_object)
	{
		if (a_index >= scriptListCount) {
			return false;
		}

		scriptAddedLists[a_index] = a_object.release();
		AddLevObjectsChange();
		return true;
	}

	bool TESLeveledList::RemoveNthScriptLevObject(std::uint8_t a_index)
	{
		if (a_index >= scriptListCount) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(scriptListCount - 1);

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < a_index; i++) {
			newData[i] = scriptAddedLists[i];
		}

		for (auto i = static_cast<std::uint8_t>(a_index + 1); i < scriptListCount; i++) {
			newData[i - 1] = scriptAddedLists[i];
		}

		scriptAddedLists = std::move(newData);
		scriptListCount = newCount;

		AddLevObjectsChange();
		return true;
	}

	bool TESLeveledList::AddEditorLevObject(LEVELED_OBJECT& a_object)
	{
		if (baseListCount >= MAX_OBJECT_COUNT) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(baseListCount + 1);

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < baseListCount; i++) {
			newData[i] = leveledLists[i];
		}

		newData[baseListCount] = a_object;

		leveledLists = std::move(newData);
		baseListCount = newCount;
		return true;
	}

	bool TESLeveledList::AddScriptLevObject(std::unique_ptr<LEVELED_OBJECT> a_object)
	{
		if (scriptListCount >= MAX_OBJECT_COUNT) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(scriptListCount + 1);

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < scriptListCount; i++) {
			newData[i] = scriptAddedLists[i];
		}

		newData[scriptListCount] = a_object.release();

		scriptAddedLists = std::move(newData);
		scriptListCount = newCount;

		AddLevObjectsChange();
		return true;
	}

	void TESLeveledList::AddEditorLevObjects(std::span<LEVELED_OBJECT> a_objects)
	{
		if (a_objects.empty()) {
			return;
		}

		const auto newCount = static_cast<std::uint8_t>(std::min(baseListCount + a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < baseListCount; i++) {
			newData[i] = leveledLists[i];
		}

		for (auto i = 0ui8; i < a_objects.size() && baseListCount + i < MAX_OBJECT_COUNT; i++) {
			newData[baseListCount + i] = a_objects[i];
		}

		leveledLists = std::move(newData);
		baseListCount = newCount;
	}

	void TESLeveledList::AddScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects)
	{
		if (a_objects.empty()) {
			return;
		}

		const auto newCount = static_cast<std::uint8_t>(std::min(scriptListCount + a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = 0ui8; i < scriptListCount; i++) {
			newData[i] = scriptAddedLists[i];
		}

		for (auto i = 0ui8; i < a_objects.size() && scriptListCount + i < MAX_OBJECT_COUNT; i++) {
			newData[scriptListCount + i] = a_objects[i].release();
		}

		scriptAddedLists = std::move(newData);
		scriptListCount = newCount;

		AddLevObjectsChange();
	}

	void TESLeveledList::ClearLevObjects()
	{
		ClearEditorLevObjects();
		ClearScriptLevObjects();
	}

	void TESLeveledList::ClearEditorLevObjects()
	{
		leveledLists.deallocate_bytes();
		baseListCount = 0;
	}

	void TESLeveledList::ClearScriptLevObjects()
	{
		if (!scriptAddedLists.data()) {
			scriptListCount = 0;
			return;
		}

		for (auto i = 0ui8; i < scriptListCount; i++) {
			auto*& object = scriptAddedLists[i];
			if (!object) {
				continue;
			}

			delete object;
			object = nullptr;
		}

		scriptAddedLists.deallocate_bytes();
		scriptListCount = 0;

		AddLevObjectsChange();
	}

	bool TESLeveledList::AddLevObjectsChange()
	{
		auto* form = DynamicCast<TESForm*>(this);
		if (!form) {
			return false;
		}

		form->AddChange(ChangeFlags::kAddedObject);
		return true;
	}

	BSContainer::ForEachResult TESLeveledList::ForEachLevObject(
		const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const
	{
		if (ForEachEditorLevObject(a_predicate) == BSContainer::ForEachResult::kStop) {
			return BSContainer::ForEachResult::kStop;
		}

		if (ForEachScriptLevObject(a_predicate) == BSContainer::ForEachResult::kStop) {
			return BSContainer::ForEachResult::kStop;
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESLeveledList::ForEachEditorLevObject(
		const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const
	{
		if (!leveledLists.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui8; i < baseListCount; i++) {
			auto& object = const_cast<LEVELED_OBJECT&>(leveledLists[i]);
			if (std::invoke(*a_predicate, std::addressof(object)) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESLeveledList::ForEachScriptLevObject(
		const REX::NotNull<std::function<BSContainer::ForEachResult(LEVELED_OBJECT*)>>& a_predicate) const
	{
		if (!scriptAddedLists.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui8; i < scriptListCount; i++) {
			auto* object = scriptAddedLists[i];
			if (std::invoke(*a_predicate, object) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}

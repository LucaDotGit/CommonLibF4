#include "RE/T/TESLeveledList.hpp"

#include "RE/B/BGSKeyword.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/L/LEVELED_OBJECT.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	auto TESLeveledList::GetSpecialChanceGlobalMap() noexcept -> BSTHashMap<const TESLeveledList*, TESGlobal*>&
	{
		static const auto SPECIAL_CHANCE_GLOBAL_MAP = REL::Relocation<BSTHashMap<const TESLeveledList*, TESGlobal*>*>{
			ID::TESLeveledList::SpecialChanceGlobalMap,
			Offset::TESLeveledList::SpecialChanceGlobalMap
		};
		return *SPECIAL_CHANCE_GLOBAL_MAP;
	}

	void TESLeveledList::CalculateCurrentFormList(
		std::uint16_t a_level,
		std::uint16_t a_count,
		BSScrapArray<CALCED_OBJECT>& a_outCalc,
		LeveledListAllBelowForce a_allBelowForce,
		bool a_clampToPlayer,
		INSTANCE_FILTER* a_instanceFilter,
		const char* a_overrideName)
	{
		using FuncType = decltype(&TESLeveledList::CalculateCurrentFormList);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESLeveledList::CalculateCurrentFormList);
		std::invoke(
			FUNC,
			this,
			a_level,
			a_count,
			a_outCalc,
			a_allBelowForce,
			a_clampToPlayer,
			a_instanceFilter,
			a_overrideName);
	}

	void TESLeveledList::CalculateCurrentFormListForRef(
		TESObjectREFR* a_ref,
		BSScrapArray<CALCED_OBJECT>& a_outCalc,
		bool a_legendary)
	{
		using FuncType = decltype(&TESLeveledList::CalculateCurrentFormListForRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESLeveledList::CalculateCurrentFormListForRef);
		std::invoke(FUNC, this, a_ref, a_outCalc, a_legendary);
	}

	auto TESLeveledList::GetKeywordChances() const -> std::optional<BSTArray<std::pair<BGSKeyword*, std::uint32_t>>>
	{
		if (!keywordChances) {
			return std::nullopt;
		}

		auto result = BSTArray<std::pair<BGSKeyword*, std::uint32_t>>();
		result.reserve(keywordChances->size());

		for (auto&& [keywordForm, chance] : *keywordChances) {
			auto* keyword = DynamicCast<BGSKeyword*>(keywordForm);
			if (!keyword) {
				continue;
			}

			result.emplace_back(keyword, chance.uint32);
		}

		return result;
	}

	void TESLeveledList::SetKeywordChances(std::span<const std::pair<BGSKeyword*, std::uint32_t>> a_chances)
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

		for (auto&& [keyword, chance] : a_chances) {
			newData->emplace_back(keyword, chance);
		}

		keywordChances = newData;
	}

	auto TESLeveledList::GetLevObjectCount() const noexcept -> std::uint8_t
	{
		return GetEditorLevObjectCount() + GetScriptLevObjectCount();
	}

	auto TESLeveledList::GetEditorLevObjectCount() const noexcept -> std::uint8_t
	{
		return baseListCount;
	}

	auto TESLeveledList::GetScriptLevObjectCount() const noexcept -> std::uint8_t
	{
		return scriptListCount;
	}

	auto TESLeveledList::GetEditorLevObjects() noexcept -> std::span<LEVELED_OBJECT>
	{
		return {leveledLists.data(), baseListCount};
	}

	auto TESLeveledList::GetEditorLevObjects() const noexcept -> std::span<LEVELED_OBJECT const>
	{
		return {leveledLists.data(), baseListCount};
	}

	void TESLeveledList::SetEditorLevObjects(std::span<LEVELED_OBJECT> a_objects)
	{
		ClearEditorLevObjects();

		if (a_objects.empty()) {
			return;
		}

		const auto newCount =
			static_cast<std::uint8_t>(std::min(a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < newCount; i++) {
			newData[i] = a_objects[i];
		}

		leveledLists = std::move(newData);
		baseListCount = newCount;
	}

	auto TESLeveledList::GetScriptLevObjects() noexcept -> std::span<LEVELED_OBJECT*>
	{
		return {scriptAddedLists.data(), scriptListCount};
	}

	auto TESLeveledList::GetScriptLevObjects() const noexcept -> std::span<LEVELED_OBJECT* const>
	{
		return {scriptAddedLists.data(), scriptListCount};
	}

	void TESLeveledList::SetScriptLevObjects(std::span<std::unique_ptr<LEVELED_OBJECT>> a_objects)
	{
		ClearScriptLevObjects();

		if (a_objects.empty()) {
			return;
		}

		const auto newCount =
			static_cast<std::uint8_t>(std::min(a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < newCount; i++) {
			newData[i] = a_objects[i].release();
		}

		scriptAddedLists = std::move(newData);
		scriptListCount = newCount;

		AddLevObjectsChange();
	}

	auto TESLeveledList::GetNthLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*
	{
		if (a_index < baseListCount) {
			return GetNthEditorLevObject(a_index);
		}

		return GetNthScriptLevObject(a_index - baseListCount);
	}

	auto TESLeveledList::SetNthLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object) -> bool
	{
		if (a_index < baseListCount) {
			return SetNthEditorLevObject(a_index, a_object);
		}

		return SetNthScriptLevObject(a_index - baseListCount, std::make_unique<LEVELED_OBJECT>(a_object));
	}

	auto TESLeveledList::RemoveNthLevObject(std::uint8_t a_index) -> bool
	{
		if (a_index < baseListCount) {
			return RemoveNthEditorLevObject(a_index);
		}

		return RemoveNthScriptLevObject(a_index - baseListCount);
	}

	auto TESLeveledList::GetNthEditorLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*
	{
		return a_index < baseListCount ? const_cast<LEVELED_OBJECT*>(std::addressof(leveledLists[a_index])) : nullptr;
	}

	auto TESLeveledList::SetNthEditorLevObject(std::uint8_t a_index, const LEVELED_OBJECT& a_object) -> bool
	{
		if (a_index >= baseListCount) {
			return false;
		}

		leveledLists[a_index] = a_object;
		return true;
	}

	auto TESLeveledList::RemoveNthEditorLevObject(std::uint8_t a_index) -> bool
	{
		if (a_index >= baseListCount) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(baseListCount - 1);

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < a_index; i++) {
			newData[i] = leveledLists[i];
		}

		for (auto i = static_cast<std::uint8_t>(a_index + 1); i < baseListCount; i++) {
			newData[i - 1] = leveledLists[i];
		}

		leveledLists = std::move(newData);
		baseListCount = newCount;
		return true;
	}

	auto TESLeveledList::GetNthScriptLevObject(std::uint8_t a_index) const -> LEVELED_OBJECT*
	{
		return a_index < scriptListCount ? scriptAddedLists[a_index] : nullptr;
	}

	auto TESLeveledList::SetNthScriptLevObject(std::uint8_t a_index, std::unique_ptr<LEVELED_OBJECT> a_object) -> bool
	{
		if (a_index >= scriptListCount) {
			return false;
		}

		scriptAddedLists[a_index] = a_object.release();
		AddLevObjectsChange();
		return true;
	}

	auto TESLeveledList::RemoveNthScriptLevObject(std::uint8_t a_index) -> bool
	{
		if (a_index >= scriptListCount) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(scriptListCount - 1);

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < a_index; i++) {
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

	auto TESLeveledList::AddEditorLevObject(LEVELED_OBJECT& a_object) -> bool
	{
		if (baseListCount >= MAX_OBJECT_COUNT) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(baseListCount + 1);

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < baseListCount; i++) {
			newData[i] = leveledLists[i];
		}

		newData[baseListCount] = a_object;

		leveledLists = std::move(newData);
		baseListCount = newCount;
		return true;
	}

	auto TESLeveledList::AddScriptLevObject(std::unique_ptr<LEVELED_OBJECT> a_object) -> bool
	{
		if (scriptListCount >= MAX_OBJECT_COUNT) {
			return false;
		}

		const auto newCount = static_cast<std::uint8_t>(scriptListCount + 1);

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < scriptListCount; i++) {
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

		const auto newCount = static_cast<std::uint8_t>(
			std::min(baseListCount + a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < baseListCount; i++) {
			newData[i] = leveledLists[i];
		}

		for (auto i = static_cast<std::uint8_t>(0); i < a_objects.size() && baseListCount + i < MAX_OBJECT_COUNT; i++) {
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

		const auto newCount = static_cast<std::uint8_t>(
			std::min(scriptListCount + a_objects.size(), static_cast<std::size_t>(MAX_OBJECT_COUNT)));

		auto newData = SimpleArray<LEVELED_OBJECT*>();
		newData.allocate_bytes(newCount);

		for (auto i = static_cast<std::uint8_t>(0); i < scriptListCount; i++) {
			newData[i] = scriptAddedLists[i];
		}

		for (auto i = static_cast<std::uint8_t>(0); i < a_objects.size() && scriptListCount + i < MAX_OBJECT_COUNT;
			 i++) {
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

		for (auto i = static_cast<std::uint8_t>(0); i < scriptListCount; i++) {
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

	auto TESLeveledList::AddLevObjectsChange() -> bool
	{
		auto* form = DynamicCast<TESForm*>(this);
		if (!form) {
			return false;
		}

		form->AddChange(ChangeFlags::AddedObject);
		return true;
	}

	auto TESLeveledList::ForEachLevObject(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (ForEachEditorLevObject(a_predicate) == BSContainer::ForEachResult::Stop) {
			return BSContainer::ForEachResult::Stop;
		}

		if (ForEachScriptLevObject(a_predicate) == BSContainer::ForEachResult::Stop) {
			return BSContainer::ForEachResult::Stop;
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto TESLeveledList::ForEachEditorLevObject(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!leveledLists.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint8_t>(0); i < baseListCount; i++) {
			auto& object = const_cast<LEVELED_OBJECT&>(leveledLists[i]);
			if (std::invoke(a_predicate.get(), std::addressof(object)) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto TESLeveledList::ForEachScriptLevObject(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(LEVELED_OBJECT*) const>>& a_predicate)
		const -> BSContainer::ForEachResult
	{
		if (!scriptAddedLists.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint8_t>(0); i < scriptListCount; i++) {
			auto* object = scriptAddedLists[i];
			if (std::invoke(a_predicate.get(), object) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}

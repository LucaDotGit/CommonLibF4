#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::UIUtils
{
	using ComparisonItems = BSScrapArray<BSTPair<const BGSInventoryItem*, std::uint32_t>>;

	void GetComparisonItems(const TESBoundObject* a_object, ComparisonItems& a_comparisonItems);
	bool HasRequiredInventoryForCraftingMenu(TESObjectREFR* a_furniture);
	void PlayPipboySound(const char* a_soundName);
	void PlayMenuSound(const char* a_soundName);
	void ShowCraftingMenu(TESObjectREFR* a_furniture);
	void UpdateGamepadDependentButtonCodes(bool a_usingGamepad);
}

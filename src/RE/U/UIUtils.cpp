#include "RE/U/UIUtils.hpp"

namespace RE::UIUtils
{
	void GetComparisonItems(const TESBoundObject* a_object, ComparisonItems& a_comparisonItems)
	{
		using FuncType = decltype(&UIUtils::GetComparisonItems);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::GetComparisonItems };
		std::invoke(FUNC, a_object, a_comparisonItems);
	}

	bool HasRequiredInventoryForCraftingMenu(TESObjectREFR* a_furniture)
	{
		using FuncType = decltype(&UIUtils::HasRequiredInventoryForCraftingMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::HasRequiredInventoryForCraftingMenu };
		return std::invoke(FUNC, a_furniture);
	}

	void PlayPipboySound(const char* a_soundName)
	{
		using FuncType = decltype(&UIUtils::PlayPipboySound);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::PlayPipboySound };
		std::invoke(FUNC, a_soundName);
	}

	void PlayMenuSound(const char* a_soundName)
	{
		using FuncType = decltype(&UIUtils::PlayMenuSound);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::PlayMenuSound };
		std::invoke(FUNC, a_soundName);
	}

	void ShowCraftingMenu(TESObjectREFR* a_furniture)
	{
		using FuncType = decltype(&UIUtils::ShowCraftingMenu);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::ShowCraftingMenu };
		std::invoke(FUNC, a_furniture);
	}

	void UpdateGamepadDependentButtonCodes(bool a_usingGamepad)
	{
		using FuncType = decltype(&UIUtils::UpdateGamepadDependentButtonCodes);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::UIUtils::UpdateGamepadDependentButtonCodes };
		std::invoke(FUNC, a_usingGamepad);
	}
}

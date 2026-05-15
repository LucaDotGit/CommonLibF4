#include "RE/P/PipboyInventoryUtils.hpp"

namespace RE::PipboyInventoryUtils
{
	bool PipboyInventoryUtilsDoSlotsOverlap(const TESObjectARMO* a_armor1, const TESObjectARMO* a_armor2)
	{
		using FuncType = decltype(&PipboyInventoryUtils::DoSlotsOverlap);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryUtils::DoSlotsOverlap };
		return std::invoke(FUNC, a_armor1, a_armor2);
	}

	void FillDamageTypeInfo(const BGSInventoryItem& a_item, const BGSInventoryItem::Stack* a_stack, BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_damageValuesPerType)
	{
		using FuncType = decltype(&PipboyInventoryUtils::FillDamageTypeInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryUtils::FillDamageTypeInfo };
		std::invoke(FUNC, a_item, a_stack, a_damageValuesPerType);
	}

	void FillResistTypeInfo(const BGSInventoryItem& a_item, const BGSInventoryItem::Stack* a_stack, BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_resistValuesPerType, REX::Float32 a_scale)
	{
		using FuncType = decltype(&PipboyInventoryUtils::FillResistTypeInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryUtils::FillResistTypeInfo };
		std::invoke(FUNC, a_item, a_stack, a_resistValuesPerType, a_scale);
	}
}

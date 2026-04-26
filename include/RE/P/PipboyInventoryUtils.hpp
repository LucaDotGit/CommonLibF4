#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE::PipboyInventoryUtils
{
	enum class PAPER_DOLL_ARMOR_SLOTS : std::int32_t
	{
		kUnderwear = 0,
		kLeftLeg = 1,
		kRightLeg = 2,
		kLeftArm = 3,
		kRightArm = 4,
		kTorso = 5,
		kHelmet = 6,
		kGoggles = 7,
		kGasMask = 8
	};

	[[nodiscard]] bool DoSlotsOverlap(const TESObjectARMO* a_armor1, const TESObjectARMO* a_armor2);
	void FillDamageTypeInfo(const BGSInventoryItem& a_item, const BGSInventoryItem::Stack* a_stack, BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_damageValuesPerType);
	void FillResistTypeInfo(const BGSInventoryItem& a_item, const BGSInventoryItem::Stack* a_stack, BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_resistValuesPerType, REX::Float32 a_scale);
}

#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE::PipboyInventoryUtils
{
	enum class PAPER_DOLL_ARMOR_SLOTS : std::int32_t
	{
		Underwear = 0,
		LeftLeg = 1,
		RightLeg = 2,
		LeftArm = 3,
		RightArm = 4,
		Torso = 5,
		Helmet = 6,
		Goggles = 7,
		GasMask = 8
	};

	[[nodiscard]]
	auto DoSlotsOverlap(const TESObjectARMO* a_armor01, const TESObjectARMO* a_armor02) -> bool;
	void FillDamageTypeInfo(
		const BGSInventoryItem& a_item,
		const BGSInventoryItem::Stack* a_stack,
		BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_damageValuesPerType);
	void FillResistTypeInfo(
		const BGSInventoryItem& a_item,
		const BGSInventoryItem::Stack* a_stack,
		BSScrapArray<BSTPair<std::uint32_t, REX::Float32>>& a_resistValuesPerType,
		REX::Float32 a_scale);
}

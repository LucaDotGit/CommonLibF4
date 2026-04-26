#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class EquippedItemData;

	class EquippedItem
	{
	public:
		// members
		BGSObjectInstance item;			  // 00
		BGSEquipSlot* equipSlot;		  // 10
		BGSEquipIndex equipIndex;		  // 18
		NiPointer<EquippedItemData> data; // 20
	};
	static_assert(sizeof(EquippedItem) == 0x28);
}

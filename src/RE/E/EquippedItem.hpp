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
		BGSObjectInstance item;			  // 0x00
		BGSEquipSlot* equipSlot;		  // 0x10
		BGSEquipIndex equipIndex;		  // 0x18
		NiPointer<EquippedItemData> data; // 0x20
	};

	static_assert(sizeof(EquippedItem) == 0x28);
}

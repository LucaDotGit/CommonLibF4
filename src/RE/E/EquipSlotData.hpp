#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class EquipSlotData
	{
	public:
		// members
		BGSEquipSlot* equipSlot;	 // 0x00
		BSFixedString equipSlotNode; // 0x08
	};

	static_assert(sizeof(EquipSlotData) == 0x10);
}

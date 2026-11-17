#pragma once

namespace RE
{
	class ObjectEquipParams
	{
	public:
		// members
		std::uint32_t stackID;			 // 0x00
		std::uint32_t number;			 // 0x04
		BGSEquipSlot* equipSlot;		 // 0x08
		BGSEquipSlot* slotBeingReplaced; // 0x10
		bool queueEquip;				 // 0x18
		bool forceEquip;				 // 0x19
		bool playEquipSounds;			 // 0x1A
		bool applyNow;					 // 0x1B
		bool locked;					 // 0x1C
		bool extraWasDeleted;			 // 0x1D
	};

	static_assert(sizeof(ObjectEquipParams) == 0x20);
}

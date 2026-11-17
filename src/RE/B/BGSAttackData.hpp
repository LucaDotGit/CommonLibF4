#pragma once

#include "RE/A/AttackData.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSAttackData : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAttackData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAttackData;

		// members
		BSFixedString event;			 // 0x10
		AttackData data;				 // 0x18
		BGSEquipSlot* weaponEquipSlot;	 // 0x50
		BGSEquipSlot* requiredEquipSlot; // 0x58
	};

	static_assert(sizeof(BGSAttackData) == 0x60);
}

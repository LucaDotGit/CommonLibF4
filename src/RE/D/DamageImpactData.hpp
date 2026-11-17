#pragma once

#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkNPCollisionObject;

	class DamageImpactData
	{
		// members
		NiPoint3A location;						// 0x00
		NiPoint3A normal;						// 0x10
		NiPoint3A velocity;						// 0x20
		NiPointer<bhkNPCollisionObject> colObj; // 0x30
	};

	static_assert(sizeof(DamageImpactData) == 0x40);
}

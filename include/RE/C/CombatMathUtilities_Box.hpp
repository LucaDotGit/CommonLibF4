#pragma once

#include "RE/C/CombatMathUtilities_ShapeT.hpp"
#include "RE/N/NiMatrix3.hpp"

namespace RE::CombatMathUtilities
{
	class Box
		: public ShapeT<Box>
	{
	public:
		// members
		NiMatrix3 orientation; // 10
		NiPoint3 center;	   // 40
		NiPoint3 halfExtends;  // 4C
	};
	static_assert(sizeof(Box) == 0x60);
}

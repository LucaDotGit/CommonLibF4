#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiPlane
	{
	public:
		// members
		NiPoint3 normal;	   // 00
		REX::Float32 constant; // 0C
	};
	static_assert(sizeof(NiPlane) == 0x10);
}

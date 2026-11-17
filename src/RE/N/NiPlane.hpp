#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiPlane
	{
	public:
		// members
		NiPoint3 normal;	   // 0x00
		REX::Float32 constant; // 0x0C
	};

	static_assert(sizeof(NiPlane) == 0x10);
}

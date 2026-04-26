#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class TESForm;

	class WORLD_LOCATION
	{
	public:
		// members
		TESForm* locationForm;	// 00
		NiPoint3 locationPoint; // 08
		REX::Float32 zRotation; // 14
	};
	static_assert(sizeof(WORLD_LOCATION) == 0x18);
}

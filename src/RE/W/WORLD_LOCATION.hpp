#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class TESForm;

	class WORLD_LOCATION
	{
	public:
		// members
		TESForm* locationForm;	// 0x00
		NiPoint3 locationPoint; // 0x08
		REX::Float32 zRotation; // 0x14
	};

	static_assert(sizeof(WORLD_LOCATION) == 0x18);
}

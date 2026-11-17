#pragma once

#include "RE/N/NiPoint2.hpp"

namespace RE
{
	class TESRegionPoint
	{
	public:
		// members
		NiPoint2 point; // 0x00
	};

	static_assert(sizeof(TESRegionPoint) == 0x08);
}

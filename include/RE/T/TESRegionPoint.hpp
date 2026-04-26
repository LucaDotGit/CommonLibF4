#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class TESRegionPoint
	{
	public:
		// members
		NiPoint2 point; // 00
	};
	static_assert(sizeof(TESRegionPoint) == 0x08);
}

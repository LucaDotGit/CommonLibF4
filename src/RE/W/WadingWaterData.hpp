#pragma once

#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class WadingWaterData
	{
	public:
		// members
		NiPoint2 lastPlaceOffset;	 // 0x00
		NiPoint2 lastDisplaceOffset; // 0x08
		NiPoint3 lastPosition;		 // 0x10
	};

	static_assert(sizeof(WadingWaterData) == 0x1C);
}

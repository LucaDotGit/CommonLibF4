#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class WadingWaterData
	{
	public:
		// members
		NiPoint2 lastPlaceOffset;	 // 00
		NiPoint2 lastDisplaceOffset; // 08
		NiPoint3 lastPosition;		 // 10
	};
	static_assert(sizeof(WadingWaterData) == 0x1C);
}

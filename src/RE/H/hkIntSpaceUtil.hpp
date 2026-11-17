#pragma once

#include "RE/H/hkAabb.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkIntSpaceUtil
	{
	public:
		// members
		hkVector4 bitOffsetLow;	 // 0x00
		hkVector4 bitOffsetHigh; // 0x10
		hkVector4 bitScale;		 // 0x20
		hkVector4 bitScaleInv;	 // 0x30
		hkAabb aabb;			 // 0x40
	};

	static_assert(sizeof(hkIntSpaceUtil) == 0x60);
}

#pragma once

#include "RE/H/hkAabb.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkIntSpaceUtil
	{
	public:
		// members
		hkVector4 bitOffsetLow;	 // 00
		hkVector4 bitOffsetHigh; // 10
		hkVector4 bitScale;		 // 20
		hkVector4 bitScaleInv;	 // 30
		hkAabb aabb;			 // 40
	};
	static_assert(sizeof(hkIntSpaceUtil) == 0x60);
}

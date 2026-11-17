#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkcdRay
	{
	public:
		// members
		hkVector4 origin;		// 0x00
		hkVector4 direction;	// 0x10
		hkVector4 invDirection; // 0x20
	};

	static_assert(sizeof(hkcdRay) == 0x30);
}

#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkcdRay
	{
	public:
		// members
		hkVector4 origin;		// 00
		hkVector4 direction;	// 10
		hkVector4 invDirection; // 20
	};
	static_assert(sizeof(hkcdRay) == 0x30);
}

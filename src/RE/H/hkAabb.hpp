#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkAabb
	{
	public:
		// members
		hkVector4 min; // 0x00
		hkVector4 max; // 0x10
	};

	static_assert(sizeof(hkAabb) == 0x20);
}

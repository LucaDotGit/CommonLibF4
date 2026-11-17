#pragma once

#include "RE/U/UnloadedRefData.hpp"

namespace RE
{
	class SpecialRefData
	{
	public:
		// members
		BGSLocationRefType* type; // 0x00
		UnloadedRefData refData;  // 0x08
	};

	static_assert(sizeof(SpecialRefData) == 0x18);
}

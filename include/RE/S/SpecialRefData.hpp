#pragma once

#include "RE/U/UnloadedRefData.hpp"

namespace RE
{
	class SpecialRefData
	{
	public:
		// members
		BGSLocationRefType* type; // 00
		UnloadedRefData refData;  // 08
	};
	static_assert(sizeof(SpecialRefData) == 0x18);
}

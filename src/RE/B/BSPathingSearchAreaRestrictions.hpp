#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSPathingSearchAreaRestrictions
	{
	public:
		// members
		NiPoint3 center;	 // 0x00
		REX::Float32 radius; // 0x0C
	};

	static_assert(sizeof(BSPathingSearchAreaRestrictions) == 0x10);
}

#pragma once

#include "RE/B/BSPathingAvoidNodeArray.hpp"
#include "RE/B/BSPathingSearchAreaRestrictions.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSPathingRestrictions
	{
	public:
		// members
		NiPointer<BSPathingAvoidNodeArray> avoidNodeArray; // 0x00
		BSPathingSearchAreaRestrictions areaRestrictions;  // 0x08
	};

	static_assert(sizeof(BSPathingRestrictions) == 0x18);
}

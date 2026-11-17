#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BGSBodyPartDefs
{
	class HitReactionData
	{
	public:
		// members
		BSFixedString chainStart; // 0x00
		BSFixedString chainEnd;	  // 0x08
		BSFixedString variableX;  // 0x10
		BSFixedString variableY;  // 0x18
		BSFixedString variableZ;  // 0x20
	};

	static_assert(sizeof(HitReactionData) == 0x28);
}

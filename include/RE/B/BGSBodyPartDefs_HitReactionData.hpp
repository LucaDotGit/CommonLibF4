#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BGSBodyPartDefs
{
	class HitReactionData
	{
	public:
		// members
		BSFixedString chainStart; // 00
		BSFixedString chainEnd;	  // 08
		BSFixedString variableX;  // 10
		BSFixedString variableY;  // 18
		BSFixedString variableZ;  // 20
	};
	static_assert(sizeof(HitReactionData) == 0x28);
}

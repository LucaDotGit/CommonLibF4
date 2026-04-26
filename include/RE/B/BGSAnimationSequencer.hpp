#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSActionData;

	class BGSAnimationSequencer
	{
	public:
		// members
		std::uint32_t numSequences;						   // 00
		BSTHashMap<BSFixedString, BGSActionData*> actions; // 08
	};
	static_assert(sizeof(BGSAnimationSequencer) == 0x38);
}

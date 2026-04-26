#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class CREATURE_SOUND;

	class CreatureSounds
	{
	public:
		// members
		BSTArray<CREATURE_SOUND> consciousLoops; // 00
		bool stopLoopWhenUnconscious;			 // 18
	};
	static_assert(sizeof(CreatureSounds) == 0x20);
}

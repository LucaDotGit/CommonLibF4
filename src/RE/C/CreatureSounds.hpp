#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class CREATURE_SOUND;

	class CreatureSounds
	{
	public:
		// members
		BSTArray<CREATURE_SOUND> consciousLoops; // 0x00
		bool stopLoopWhenUnconscious;			 // 0x18
	};

	static_assert(sizeof(CreatureSounds) == 0x20);
}

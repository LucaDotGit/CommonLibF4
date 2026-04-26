#pragma once

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t
	{
		kUnlocked = -1,
		kEasy = 0,
		kAverage = 1,
		kHard = 2,
		kVeryHard = 3,
		kRequiresKey = 4,
		kInaccessible = 5,
		kTerminal = 6,
		kBarred = 7,
		kChained = 8
	};
}

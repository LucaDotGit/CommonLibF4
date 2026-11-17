#pragma once

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t
	{
		Unlocked = -1,
		Easy = 0,
		Average = 1,
		Hard = 2,
		VeryHard = 3,
		RequiresKey = 4,
		Inaccessible = 5,
		Terminal = 6,
		Barred = 7,
		Chained = 8
	};
}

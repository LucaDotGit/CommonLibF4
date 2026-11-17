#pragma once

namespace RE
{
	enum class GUN_STATE : std::uint32_t
	{
		Drawn = 0,
		Relaxed = 1,
		Blocked = 2,
		Alert = 3,
		Reloading = 4,
		Throwing = 5,
		Sighted = 6,
		Fire = 7,
		FireSighted = 8
	};
}

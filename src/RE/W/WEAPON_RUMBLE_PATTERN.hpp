#pragma once

namespace RE
{
	enum class WEAPON_RUMBLE_PATTERN : std::int32_t
	{
		Constant = 0,
		PeriodicSquare = 1,
		PeriodicTriangle = 2,
		PeriodicSawtooth = 3,
		PatternCount = 4
	};
}

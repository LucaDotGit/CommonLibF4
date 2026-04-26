#pragma once

namespace RE
{
	enum class WEAPON_RUMBLE_PATTERN : std::int32_t
	{
		kConstant = 0,
		kPeriodicSquare = 1,
		kPeriodicTriangle = 2,
		kPeriodicSawtooth = 3,
		kPatternCount = 4
	};
}

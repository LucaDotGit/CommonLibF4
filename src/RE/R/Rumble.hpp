#pragma once

namespace RE::Rumble
{
	enum class RUMBLE_TYPE : std::int32_t
	{
		BigMotor = 0,
		SmallMotor = 1
	};

	enum class RUMBLE_PATTERN : std::int32_t
	{
		Constant = 0,
		PeriodicSquare = 1,
		PeriodicTriangle = 2,
		PeriodicSawtooth = 3
	};

	class AutoRumblePause
	{
	public:
	};

	static_assert(std::is_empty_v<AutoRumblePause>);
}

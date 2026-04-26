#pragma once

namespace RE::Rumble
{
	enum class RUMBLE_TYPE : std::int32_t
	{
		kBigMotor = 0,
		kSmallMotor = 1
	};

	enum class RUMBLE_PATTERN : std::int32_t
	{
		kConstant = 0,
		kPeriodicSquare = 1,
		kPeriodicTriangle = 2,
		kPeriodicSawtooth = 3
	};

	class AutoRumblePause
	{
	public:
	};
	static_assert(std::is_empty_v<AutoRumblePause>);
}

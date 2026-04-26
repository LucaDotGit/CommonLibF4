#pragma once

namespace RE::Movement
{
	enum class SPEED_DIRECTION : std::int32_t
	{
		kLeft = 0,
		kRight = 1,
		kForward = 2,
		kBackward = 3,
		kPitch = 4,
		kRoll = 5,
		kYaw = 6,

		kTotal = 7
	};
}

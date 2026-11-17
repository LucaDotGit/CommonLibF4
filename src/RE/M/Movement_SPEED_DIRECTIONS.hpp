#pragma once

namespace RE::Movement
{
	enum class SPEED_DIRECTION : std::int32_t
	{
		Left = 0,
		Right = 1,
		Forward = 2,
		Backward = 3,
		Pitch = 4,
		Roll = 5,
		Yaw = 6,

		_Count = 7
	};
}

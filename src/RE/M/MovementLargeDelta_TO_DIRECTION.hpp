#pragma once

namespace RE::MovementLargeDelta
{
	enum class TO_DIRECTION : std::int32_t
	{
		FacingForward = 0,
		StrafingRight = 1,
		StrafingBackward = 2,
		StrafingLeft = 3,
		FacingRight = 4,
		FacingBackward = 5,
		FacingLeft = 6,

		_Count = 7
	};
}

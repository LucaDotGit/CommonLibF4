#pragma once

namespace RE::MovementLargeDelta
{
	enum class FROM_DIRECTION : std::int32_t
	{
		FacingForward = 0,
		StrafingRight = 1,
		StrafingBackward = 2,
		StrafingLeft = 3,

		_Count = 4
	};
}

#pragma once

namespace RE::MovementLargeDelta
{
	enum class FROM_DIRECTION : std::int32_t
	{
		kFacingForward = 0,
		kStrafingRight = 1,
		kStrafingBackward = 2,
		kStrafingLeft = 3,

		kTotal = 4
	};
}

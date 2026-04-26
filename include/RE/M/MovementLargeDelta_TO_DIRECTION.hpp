#pragma once

namespace RE::MovementLargeDelta
{
	enum class TO_DIRECTION : std::int32_t
	{
		kFacingForward = 0,
		kStrafingRight = 1,
		kStrafingBackward = 2,
		kStrafingLeft = 3,
		kFacingRight = 4,
		kFacingBackward = 5,
		kFacingLeft = 6,

		kTotal = 7
	};
}

#pragma once

namespace RE
{
	enum class FLY_STATE : std::uint32_t
	{
		kNone = 0,
		kTakeOff = 1,
		kCruising = 2,
		kHovering = 3,
		kLanding = 4,
		kPerching = 5,
		kAction = 6
	};
}

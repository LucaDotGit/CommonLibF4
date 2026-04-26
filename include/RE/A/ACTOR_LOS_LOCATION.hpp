#pragma once

namespace RE
{
	enum class ACTOR_LOS_LOCATION : std::int32_t
	{
		kNone = 0,
		kEye = 1,
		kHead = 2,
		kTorse = 3,
		kFeet = 4,

		kTotal = 5
	};
}

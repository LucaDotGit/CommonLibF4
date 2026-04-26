#pragma once

namespace RE
{
	enum class ACTOR_STANCE : std::uint32_t
	{
		kNormal = 0,
		kSneaking = 1,
		kCoverVeryLow = 2,
		kCoverLow = 3,
		kCoverMedium = 4,
		kCoverHigh = 5,

		kTotal = 6
	};
}

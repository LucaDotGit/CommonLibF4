#pragma once

namespace RE
{
	enum class ACTOR_STANCE : std::uint32_t
	{
		Normal = 0,
		Sneaking = 1,
		CoverVeryLow = 2,
		CoverLow = 3,
		CoverMedium = 4,
		CoverHigh = 5,

		_Count = 6
	};
}

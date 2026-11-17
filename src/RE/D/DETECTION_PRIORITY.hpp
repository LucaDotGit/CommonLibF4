#pragma once

namespace RE
{
	enum class DETECTION_PRIORITY : std::int32_t
	{
		None = 0,
		VeryLow = 1,
		Low = 2,
		Normal = 3,
		High = 4,
		Critical = 5
	};
}

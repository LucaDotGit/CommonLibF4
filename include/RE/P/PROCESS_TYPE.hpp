#pragma once

namespace RE
{
	enum class PROCESS_TYPE : std::int32_t
	{
		kHigh = 0,
		kMiddleHigh = 1,
		kMiddleLow = 2,
		kLow = 3,

		kMin = kHigh,
		kMax = kLow,

		kTotal = (kMax - kMin) + 1
	};
}

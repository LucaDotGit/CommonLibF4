#pragma once

namespace RE
{
	enum class PROCESS_TYPE : std::int32_t
	{
		High = 0,
		MiddleHigh = 1,
		MiddleLow = 2,
		Low = 3,

		_Min = High,
		_Max = Low,

		_Count = _Max + 1
	};
}

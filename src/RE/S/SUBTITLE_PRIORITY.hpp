#pragma once

namespace RE
{
	enum class SUBTITLE_PRIORITY : std::int32_t
	{
		Low = 0,
		Normal = 1,
		High = 2,
		Force = 3,

		_Count = 4
	};
}

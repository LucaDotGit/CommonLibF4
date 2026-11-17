#pragma once

namespace RE
{
	enum class ACTOR_CRITICAL_STAGE : std::int32_t
	{
		None = 0,
		GooStart = 1,
		GooEnd = 2,
		DisintegrateStart = 3,
		DisintegrateEnd = 4,
		FreezeStart = 5,
		FreezeEnd = 6,

		_Count = 7
	};
}

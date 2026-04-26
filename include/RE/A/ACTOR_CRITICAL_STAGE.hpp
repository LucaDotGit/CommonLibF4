#pragma once

namespace RE
{
	enum class ACTOR_CRITICAL_STAGE : std::int32_t
	{
		kNone = 0,
		kGooStart = 1,
		kGooEnd = 2,
		kDisintegrateStart = 3,
		kDisintegrateEnd = 4,
		kFreezeStart = 5,
		kFreezeEnd = 6,

		kTotal = 7
	};
}

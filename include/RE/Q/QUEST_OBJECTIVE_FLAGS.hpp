#pragma once

namespace RE
{
	enum class QUEST_OBJECTIVE_FLAGS : std::int32_t
	{
		kNone = 0,
		kORWithPrevious = 1 << 0,
		kNoStatsTracking = 1 << 1
	};
}

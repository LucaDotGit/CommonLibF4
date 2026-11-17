#pragma once

namespace RE
{
	enum class QUEST_OBJECTIVE_FLAGS : std::int32_t
	{
		None = 0,
		ORWithPrevious = 1 << 0,
		NoStatsTracking = 1 << 1
	};
}

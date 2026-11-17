#pragma once

namespace RE
{
	enum class QUEST_OBJECTIVE_STATE : std::int32_t
	{
		Dormant = 0,
		Displayed = 1,
		Completed = 2,
		CompletedDisplayed = 3,
		Failed = 4,
		FailedDisplayed = 5
	};
}

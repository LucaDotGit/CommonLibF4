#pragma once

namespace RE
{
	enum class QUEST_OBJECTIVE_STATE : std::int32_t
	{
		kDormant = 0,
		kDisplayed = 1,
		kCompleted = 2,
		kCompletedDisplayed = 3,
		kFailed = 4,
		kFailedDisplayed = 5
	};
}

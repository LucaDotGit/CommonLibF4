#pragma once

namespace RE
{
	enum class SCENE_ACTION_PLAYER_RESPONSE_TYPE : std::int32_t
	{
		kPositive = 0,
		kNegative = 1,
		kNeutral = 2,
		kQuestion = 3,
		kTotal = 4,
		kNone = 5
	};
}

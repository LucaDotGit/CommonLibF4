#pragma once

namespace RE
{
	enum class SCENE_ACTION_PLAYER_RESPONSE_TYPE : std::int32_t
	{
		Positive = 0,
		Negative = 1,
		Neutral = 2,
		Question = 3,
		_Count = 4,
		None = 5
	};
}

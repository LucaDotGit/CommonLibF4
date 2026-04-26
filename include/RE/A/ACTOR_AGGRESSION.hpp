#pragma once

namespace RE
{
	enum class ACTOR_AGGRESSION : std::int32_t
	{
		kCalmed = -1,
		kUnaggressive = 0,
		kAggressive = 1,
		kVeryAggressive = 2,
		kFrenzied = 3,

		kTotal = 5
	};
}

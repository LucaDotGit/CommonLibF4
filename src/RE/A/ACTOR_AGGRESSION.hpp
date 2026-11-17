#pragma once

namespace RE
{
	enum class ACTOR_AGGRESSION : std::int32_t
	{
		Calmed = -1,
		Unaggressive = 0,
		Aggressive = 1,
		VeryAggressive = 2,
		Frenzied = 3,

		_Count = 5
	};
}

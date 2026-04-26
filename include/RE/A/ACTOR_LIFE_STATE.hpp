#pragma once

namespace RE
{
	enum class ACTOR_LIFE_STATE : std::uint32_t
	{
		kAlive = 0,
		kDying = 1,
		kDead = 2,
		kUnconscious = 3,
		kReanimate = 4,
		kRecycle = 5,
		kRestrained = 6,
		kEssentialDown = 7,
		kBleedout = 8
	};
}

#pragma once

namespace RE
{
	enum class ACTOR_MOVEMENT_TYPE : std::uint32_t
	{
		kWalk = 0,
		kRun = 1,
		kSneak = 2,
		kBleedout = 3,
		kSwim = 4
	};
}

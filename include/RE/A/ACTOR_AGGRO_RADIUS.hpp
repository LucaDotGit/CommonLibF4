#pragma once

namespace RE
{
	enum class ACTOR_AGGRO_RADIUS : std::int32_t
	{
		kWarn = 0,
		kWarnAndAttack = 1,
		kAttack = 2,
		kCount = 3
	};
}

#pragma once

namespace RE
{
	enum class ACTOR_LOS_LOCATION : std::int32_t
	{
		None = 0,
		Eye = 1,
		Head = 2,
		Torse = 3,
		Feet = 4,

		_Count = 5
	};
}

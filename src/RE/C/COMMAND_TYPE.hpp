#pragma once

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t
	{
		None = 0,
		Call = 1,
		Follow = 2,
		Move = 3,
		Attack = 4,
		Inspect = 5,
		Retrieve = 6,
		Stay = 7,
		Release = 8,
		Heal = 9,
		Assign = 10,
		Ride = 11,
		Enter = 12
	};
}

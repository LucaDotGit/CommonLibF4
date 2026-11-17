#pragma once

namespace RE
{
	enum class FLY_STATE : std::uint32_t
	{
		None = 0,
		TakeOff = 1,
		Cruising = 2,
		Hovering = 3,
		Landing = 4,
		Perching = 5,
		Action = 6
	};
}

#pragma once

namespace RE
{
	enum class WEAPON_STATE : std::uint32_t
	{
		Sheathed = 0,
		WantToDraw = 1,
		Drawing = 2,
		Drawn = 3,
		WantToSheathe = 4,
		Sheathing = 5
	};
}

#pragma once

namespace RE
{
	enum class WEAPON_STATE : std::uint32_t
	{
		kSheathed = 0,
		kWantToDraw = 1,
		kDrawing = 2,
		kDrawn = 3,
		kWantToSheathe = 4,
		kSheathing = 5
	};
}

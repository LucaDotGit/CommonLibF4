#pragma once

namespace RE
{
	enum class ITEM_CHANGE_FILTER : std::uint32_t
	{
		None = 0,
		Favorites = 1 << 0,
		Weapons = 1 << 1,
		Apparel = 1 << 2,
		Aid = 1 << 3,
		Scrolls = 1 << 4,
		Food = 1 << 5,
		Ingredients = 1 << 6,
		Books = 1 << 7,
		Keys = 1 << 8,
		Misc = 1 << 9,
		Junk = 1 << 10,
		Mods = 1 << 11,
		Ammo = 1 << 12,
		Holotapes = 1 << 13,

		_Count = 14
	};
}

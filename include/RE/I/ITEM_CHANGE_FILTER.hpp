#pragma once

namespace RE
{
	enum class ITEM_CHANGE_FILTER : std::uint32_t
	{
		kNone = 0,
		kFavorites = 1 << 0,
		kWeapons = 1 << 1,
		kApparel = 1 << 2,
		kAid = 1 << 3,
		kScrolls = 1 << 4,
		kFood = 1 << 5,
		kIngredients = 1 << 6,
		kBooks = 1 << 7,
		kKeys = 1 << 8,
		kMisc = 1 << 9,
		kJunk = 1 << 10,
		kMods = 1 << 11,
		kAmmo = 1 << 12,
		kHolotapes = 1 << 13,

		kTotal = 14,

		kAll = kFavorites |
			   kWeapons |
			   kApparel |
			   kAid |
			   kScrolls |
			   kFood |
			   kIngredients |
			   kBooks |
			   kKeys |
			   kMisc |
			   kJunk |
			   kMods |
			   kAmmo |
			   kHolotapes
	};
}

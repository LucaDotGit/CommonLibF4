#pragma once

namespace RE
{
	enum class WEAPON_TYPE : std::int32_t
	{
		kNone = -1,
		kHandToHand = 0,
		kOneHandSword = 1,
		kOneHandDagger = 2,
		kOneHandAxe = 3,
		kOneHandMace = 4,
		kTwoHandSword = 5,
		kTwoHandAxe = 6,
		kBow = 7,
		kStaff = 8,
		kGun = 9,
		kGrenade = 10,
		kMine = 11
	};
}

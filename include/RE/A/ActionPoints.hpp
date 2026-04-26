#pragma once

namespace RE::ActionPoints
{
	enum class Action : std::int32_t
	{
		kUnarmed = 0,
		kOneHandMelee = 1,
		kTwoHandMelee = 2,
		kMagic = 3,
		kRanged = 4,
		kReload = 5,
		kSwitchWeapon = 6,
		kToggleWeaponDrawn = 7,
		kHeal = 8,
		kPlayerVATSDeath = 9,
		kPlayerDialogue = 10,
		kSightedEnter = 11,

		kTotal = 12
	};
}

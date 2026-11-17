#pragma once

namespace RE::ActionPoints
{
	enum class Action : std::int32_t
	{
		Unarmed = 0,
		OneHandMelee = 1,
		TwoHandMelee = 2,
		Magic = 3,
		Ranged = 4,
		Reload = 5,
		SwitchWeapon = 6,
		ToggleWeaponDrawn = 7,
		Heal = 8,
		PlayerVATSDeath = 9,
		PlayerDialogue = 10,
		SightedEnter = 11,

		_Count = 12
	};
}

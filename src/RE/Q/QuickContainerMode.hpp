#pragma once

namespace RE
{
	enum class QuickContainerMode : std::int32_t
	{
		Loot = 0,
		Teammate = 1,
		PowerArmor = 2,
		Turret = 3,
		Workshop = 4,
		Crafting = 5,
		Stealing = 6,
		StealingPowerArmor = 7
	};
}

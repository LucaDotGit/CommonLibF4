#pragma once

namespace RE
{
	enum class QuickContainerMode : std::int32_t
	{
		kLoot = 0,
		kTeammate = 1,
		kPowerArmor = 2,
		kTurret = 3,
		kWorkshop = 4,
		kCrafting = 5,
		kStealing = 6,
		kStealingPowerArmor = 7
	};
}

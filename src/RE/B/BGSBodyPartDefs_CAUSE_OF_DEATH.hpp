#pragma once

namespace RE::BGSBodyPartDefs
{
	enum class CAUSE_OF_DEATH : std::int32_t
	{
		CauseOfDeathNone = -1,
		CauseOfDeathExplosion = 0,
		CauseOfDeathGun = 1,
		CauseOfDeathBluntWeapon = 2,
		CauseOfDeathHandToHand = 3,
		CauseOfDeathObjectImpact = 4,
		CauseOfDeathPoison = 5,
		CauseOfDeathDecapitation = 6
	};
}

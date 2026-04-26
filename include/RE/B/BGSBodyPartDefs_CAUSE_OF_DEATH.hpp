#pragma once

namespace RE::BGSBodyPartDefs
{
	enum class CAUSE_OF_DEATH : std::int32_t
	{
		kCauseOfDeathNone = -1,
		kCauseOfDeathExplosion = 0,
		kCauseOfDeathGun = 1,
		kCauseOfDeathBluntWeapon = 2,
		kCauseOfDeathHandToHand = 3,
		kCauseOfDeathObjectImpact = 4,
		kCauseOfDeathPoison = 5,
		kCauseOfDeathDecapitation = 6
	};
}

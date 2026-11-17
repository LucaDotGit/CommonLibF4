#pragma once

namespace RE
{
	enum class PLAYER_ACTION : std::int32_t
	{
		None = 0,
		SwingMeleeWeapon = 1,
		CastProjectileSpell = 2,
		ShootBow = 3,
		ZKeyObject = 4,
		Jumping = 5,
		KnockingOverObjects = 6,
		StandOnTableChair = 7,
		IronSights = 8,
		DestroyObject = 9,
		LockedObject = 10,
		Pickpocket = 11,
		CastSelfSpell = 12,
		Shout = 13,
		ActorCollision = 14,
		InvalidMarker = 16
	};
}

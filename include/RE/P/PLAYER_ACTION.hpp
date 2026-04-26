#pragma once

namespace RE
{
	enum class PLAYER_ACTION : std::int32_t
	{
		kNone = 0,
		kSwingMeleeWeapon = 1,
		kCastProjectileSpell = 2,
		kShootBow = 3,
		kZKeyObject = 4,
		kJumping = 5,
		kKnockingOverObjects = 6,
		kStandOnTableChair = 7,
		kIronSights = 8,
		kDestroyObject = 9,
		kLockedObject = 10,
		kPickpocket = 11,
		kCastSelfSpell = 12,
		kShout = 13,
		kActorCollision = 14,
		kInvalidMarker = 16
	};
}

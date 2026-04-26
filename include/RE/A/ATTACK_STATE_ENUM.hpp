#pragma once

namespace RE
{
	enum class ATTACK_STATE_ENUM : std::uint32_t
	{
		kNone = 0,
		kDraw = 1,
		kSwing = 2,
		kHit = 3,
		kNextAttack = 4,
		kFollowThrough = 5,
		kBash = 6,
		kBowDraw = 8,
		kBowAttached = 9,
		kBowDrawn = 10,
		kBowReleasing = 11,
		kBowReleased = 12,
		kBowNextAttack = 13,
		kBowFollowThrough = 14,
		kFire = 15,
		kFiring = 16,
		kFired = 17
	};
}

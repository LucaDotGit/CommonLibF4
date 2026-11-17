#pragma once

namespace RE
{
	enum class ATTACK_STATE_ENUM : std::uint32_t
	{
		None = 0,
		Draw = 1,
		Swing = 2,
		Hit = 3,
		NextAttack = 4,
		FollowThrough = 5,
		Bash = 6,
		BowDraw = 8,
		BowAttached = 9,
		BowDrawn = 10,
		BowReleasing = 11,
		BowReleased = 12,
		BowNextAttack = 13,
		BowFollowThrough = 14,
		Fire = 15,
		Firing = 16,
		Fired = 17
	};
}

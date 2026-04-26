#pragma once

namespace RE
{
	enum class CHARACTER_FLAGS : std::uint32_t
	{
		kNone = 0,
		kQuadruped = 1 << 0,
		kNoGravityOnGround = 1 << 1,
		kTryStep = 1 << 2,
		kNoFriction = 1 << 3,
		kStuckQuad = 1 << 5,
		kAllowJumpNoContact = 1 << 4,
		kAnimAngleMod = 1 << 6,
		kHitDamage = 1 << 7,
		kSupport = 1 << 8,
		kHasPotentialSupportManifold = 1 << 9,
		kCanJump = 1 << 10,
		kChaseBip = 1 << 11,
		kFollowRagdoll = 1 << 12,
		kJumping = 1 << 13,
		kNotPushable = 1 << 14,
		kCheckSupport = 1 << 15,
		kNoSim = 1 << 17,
		kFarAway = 1 << 18,
		kOnStilts = 1 << 19,
		kQuickSimulate = 1 << 20,
		kRecordHits = 1 << 21,
		kComputeTiltPreIntegrate = 1 << 22,
		kShouldersUnderWater = 1 << 23,
		kOnStairs = 1 << 24,
		kCanPitch = 1 << 25,
		kCanRoll = 1 << 26,
		kNoCharacterCollisions = 1 << 27,
		kNotPushablePermanent = 1 << 28,
		kPossiblePathObstacle = 1 << 29,
		kShapeRequiresZRot = 1 << 30,
		kSwimAtWaterSurface = 1ui32 << 31
	};
}

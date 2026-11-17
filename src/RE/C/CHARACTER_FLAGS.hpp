#pragma once

namespace RE
{
	enum class CHARACTER_FLAGS : std::uint32_t
	{
		None = 0,
		Quadruped = 1 << 0,
		NoGravityOnGround = 1 << 1,
		TryStep = 1 << 2,
		NoFriction = 1 << 3,
		StuckQuad = 1 << 5,
		AllowJumpNoContact = 1 << 4,
		AnimAngleMod = 1 << 6,
		HitDamage = 1 << 7,
		Support = 1 << 8,
		HasPotentialSupportManifold = 1 << 9,
		CanJump = 1 << 10,
		ChaseBip = 1 << 11,
		FollowRagdoll = 1 << 12,
		Jumping = 1 << 13,
		NotPushable = 1 << 14,
		CheckSupport = 1 << 15,
		NoSim = 1 << 17,
		FarAway = 1 << 18,
		OnStilts = 1 << 19,
		QuickSimulate = 1 << 20,
		RecordHits = 1 << 21,
		ComputeTiltPreIntegrate = 1 << 22,
		ShouldersUnderWater = 1 << 23,
		OnStairs = 1 << 24,
		CanPitch = 1 << 25,
		CanRoll = 1 << 26,
		NoCharacterCollisions = 1 << 27,
		NotPushablePermanent = 1 << 28,
		PossiblePathObstacle = 1 << 29,
		ShapeRequiresZRot = 1 << 30,
		SwimAtWaterSurface = static_cast<std::uint32_t>(1) << 31
	};
}

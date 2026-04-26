#pragma once

namespace RE
{
	class bhkPickData;
	class NiPoint3;
}

namespace RE::CombatUtilities
{
	bool CalculateProjectileLOS(
		Actor* a_actor,
		BGSProjectile* a_projectile,
		REX::Float32 a_projectileSpeed,
		const NiPoint3& a_launchPos,
		const NiPoint3& a_targetPos,
		NiPoint3* a_hitPos,
		TESObjectREFR** a_collidee,
		REX::Float32* a_distanceFraction);

	bool CalculateProjectileLOS(Actor* a_actor, BGSProjectile* a_projectile, bhkPickData& a_pickData);

	bool CalculateProjectileTrajectory(
		const NiPoint3& a_projectilePos,
		const NiPoint3& a_projectileVelocity,
		REX::Float32 a_projectileGravity,
		const NiPoint3& a_targetPos,
		REX::Float32 a_heading,
		NiPoint3& a_trajectoryPos);

	[[nodiscard]] REX::Float32& GetWorldGravity();
}

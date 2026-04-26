#include "RE/C/CombatUtilities.hpp"

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
		REX::Float32* a_distanceFraction)
	{
		using FuncType = bool (*)(Actor*, BGSProjectile*, REX::Float32, const NiPoint3&, const NiPoint3&, NiPoint3*, TESObjectREFR**, REX::Float32*);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatUtilities::CalculateProjectileLOS01 };
		return std::invoke(FUNC, a_actor, a_projectile, a_projectileSpeed, a_launchPos, a_targetPos, a_hitPos, a_collidee, a_distanceFraction);
	}

	bool CalculateProjectileLOS(Actor* a_actor, BGSProjectile* a_projectile, bhkPickData& a_pickData)
	{
		using FuncType = bool (*)(Actor*, BGSProjectile*, bhkPickData&);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatUtilities::CalculateProjectileLOS02 };
		return std::invoke(FUNC, a_actor, a_projectile, a_pickData);
	}

	bool CalculateProjectileTrajectory(
		const NiPoint3& a_projectilePos,
		const NiPoint3& a_projectileVelocity,
		REX::Float32 a_projectileGravity,
		const NiPoint3& a_targetPos,
		REX::Float32 a_heading,
		NiPoint3& a_trajectoryPos)
	{
		using FuncType = decltype(&CombatUtilities::CalculateProjectileTrajectory);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatUtilities::CalculateProjectileTrajectory };
		return std::invoke(FUNC, a_projectilePos, a_projectileVelocity, a_projectileGravity, a_targetPos, a_heading, a_trajectoryPos);
	}

	REX::Float32& GetWorldGravity()
	{
		static const auto WORLD_GRAVITY = REL::Relocation<REX::Float32*>{ ID::CombatUtilities::WorldGravity };
		return *WORLD_GRAVITY;
	}
}

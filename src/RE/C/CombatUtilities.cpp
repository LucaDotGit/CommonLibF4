#include "RE/C/CombatUtilities.hpp"

namespace RE::CombatUtilities
{
	auto CalculateProjectileLOS(
		Actor* a_actor,
		BGSProjectile* a_projectile,
		REX::Float32 a_projectileSpeed,
		const NiPoint3& a_launchPos,
		const NiPoint3& a_targetPos,
		NiPoint3* a_hitPos,
		TESObjectREFR** a_collidee,
		REX::Float32* a_distanceFraction) -> bool
	{
		using FuncType = bool (*)(
			Actor*,
			BGSProjectile*,
			REX::Float32,
			const NiPoint3&,
			const NiPoint3&,
			NiPoint3*,
			TESObjectREFR**,
			REX::Float32*);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatUtilities::CalculateProjectileLOS01);
		return std::invoke(
			FUNC,
			a_actor,
			a_projectile,
			a_projectileSpeed,
			a_launchPos,
			a_targetPos,
			a_hitPos,
			a_collidee,
			a_distanceFraction);
	}

	auto CalculateProjectileLOS(Actor* a_actor, BGSProjectile* a_projectile, bhkPickData& a_pickData) -> bool
	{
		using FuncType = bool (*)(Actor*, BGSProjectile*, bhkPickData&);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatUtilities::CalculateProjectileLOS02);
		return std::invoke(FUNC, a_actor, a_projectile, a_pickData);
	}

	auto CalculateProjectileTrajectory(
		const NiPoint3& a_projectilePos,
		const NiPoint3& a_projectileVelocity,
		REX::Float32 a_projectileGravity,
		const NiPoint3& a_targetPos,
		REX::Float32 a_heading,
		NiPoint3& a_trajectoryPos) -> bool
	{
		using FuncType = decltype(&CombatUtilities::CalculateProjectileTrajectory);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatUtilities::CalculateProjectileTrajectory);
		return std::invoke(
			FUNC,
			a_projectilePos,
			a_projectileVelocity,
			a_projectileGravity,
			a_targetPos,
			a_heading,
			a_trajectoryPos);
	}

	auto GetWorldGravity() noexcept -> REX::Float32&
	{
		static const auto WORLD_GRAVITY = REL::Relocation<REX::Float32*>(ID::CombatUtilities::WorldGravity);
		return *WORLD_GRAVITY;
	}
}

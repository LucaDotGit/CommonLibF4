#include "RE/C/CombatFormulas.hpp"

namespace RE::CombatFormulas
{
	auto CalcResistedPercentage(
		const ActorValueInfo& a_resistance,
		REX::Float32 a_damage,
		REX::Float32 a_resistancePoints) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::CalcResistedPercentage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::CalcResistedPercentage);
		return std::invoke(FUNC, a_resistance, a_damage, a_resistancePoints);
	}

	auto CalcScopeSteadyActionPointDrain(const Actor& a_actor, REX::Float32 a_deltaTime) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::CalcScopeSteadyActionPointDrain);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::CalcScopeSteadyActionPointDrain);
		return std::invoke(FUNC, a_actor, a_deltaTime);
	}

	auto CalcTargetedLimbDamage(
		const Actor& a_target,
		const BGSBodyPart& a_bodyPart,
		REX::Float32 a_physicalDamage,
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_damageTypes) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::CalcTargetedLimbDamage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::CalcTargetedLimbDamage);
		return std::invoke(FUNC, a_target, a_bodyPart, a_physicalDamage, a_damageTypes);
	}

	auto CalcWeaponDamage(
		const TESForm* a_owner,
		const TESObjectWEAP::InstanceData* a_instanceData,
		const TESAmmo* a_ammo,
		REX::Float32 a_condition,
		REX::Float32 a_rangeMult) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::CalcWeaponDamage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::CalcWeaponDamage);
		return std::invoke(FUNC, a_owner, a_instanceData, a_ammo, a_condition, a_rangeMult);
	}

	auto CalculateAimModelWobble(const Actor& a_actor) -> REX::Float64
	{
		using FuncType = decltype(&CombatFormulas::CalculateAimModelWobble);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::CalculateAimModelWobble);
		return std::invoke(FUNC, a_actor);
	}

	auto GetNumCrippledAttackConditions(const Actor& a_actor) -> std::int64_t
	{
		using FuncType = decltype(&CombatFormulas::GetNumCrippledAttackConditions);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::GetNumCrippledAttackConditions);
		return std::invoke(FUNC, a_actor);
	}

	auto GetWeaponDisplayAccuracy(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, Actor* a_actor) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayAccuracy);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::GetWeaponDisplayAccuracy);
		return std::invoke(FUNC, a_weapon, a_actor);
	}

	auto GetWeaponDisplayDamage(
		const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
		const TESAmmo* a_ammo,
		REX::Float32 a_condition) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayDamage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::GetWeaponDisplayDamage);
		return std::invoke(FUNC, a_weapon, a_ammo, a_condition);
	}

	auto GetWeaponDisplayRange(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon) -> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayRange);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::GetWeaponDisplayRange);
		return std::invoke(FUNC, a_weapon);
	}

	auto GetWeaponDisplayRateOfFire(const TESObjectWEAP& a_weapon, const TESObjectWEAP::InstanceData* a_data)
		-> REX::Float32
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayRateOfFire);
		static const auto FUNC = REL::Relocation<FuncType>(ID::CombatFormulas::GetWeaponDisplayRateOfFire);
		return std::invoke(FUNC, a_weapon, a_data);
	}
}

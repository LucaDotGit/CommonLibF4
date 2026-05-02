#include "RE/C/CombatFormulas.hpp"

namespace RE::CombatFormulas
{
	REX::Float32 CalcResistedPercentage(const ActorValueInfo* a_resistance, REX::Float32 a_damage, REX::Float32 a_resistancePoints)
	{
		using FuncType = decltype(&CombatFormulas::CalcResistedPercentage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::CalcResistedPercentage };
		return std::invoke(FUNC, a_resistance, a_damage, a_resistancePoints);
	}

	REX::Float32 CalcTargetedLimbDamage(Actor* a_target, const BGSBodyPart* a_bodyPart, REX::Float32 a_physicalDamage, BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_damageTypes)
	{
		using FuncType = decltype(&CombatFormulas::CalcTargetedLimbDamage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::CalcTargetedLimbDamage };
		return std::invoke(FUNC, a_target, a_bodyPart, a_physicalDamage, a_damageTypes);
	}

	REX::Float64 CalculateAimModelWobble(Actor* a_actor)
	{
		using FuncType = decltype(&CombatFormulas::CalculateAimModelWobble);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::CalculateAimModelWobble };
		return std::invoke(FUNC, a_actor);
	}

	REX::Float32 CalcScopeSteadyActionPointDrain(Actor* a_actor, REX::Float32 a_deltaSec)
	{
		using FuncType = decltype(&CombatFormulas::CalcScopeSteadyActionPointDrain);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::CalcScopeSteadyActionPointDrain };
		return std::invoke(FUNC, a_actor, a_deltaSec);
	}

	std::int64_t GetNumCrippledAttackConditions(Actor* a_actor)
	{
		using FuncType = decltype(&CombatFormulas::GetNumCrippledAttackConditions);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::GetNumCrippledAttackConditions };
		return std::invoke(FUNC, a_actor);
	}

	REX::Float32 GetWeaponDisplayAccuracy(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, Actor* a_actor)
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayAccuracy);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::GetWeaponDisplayAccuracy };
		return std::invoke(FUNC, a_weapon, a_actor);
	}

	REX::Float32 GetWeaponDisplayDamage(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, const TESAmmo* a_ammo, REX::Float32 a_condition)
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayDamage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::GetWeaponDisplayDamage };
		return std::invoke(FUNC, a_weapon, a_ammo, a_condition);
	}

	REX::Float32 GetWeaponDisplayRange(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon)
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayRange);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::GetWeaponDisplayRange };
		return std::invoke(FUNC, a_weapon);
	}

	REX::Float32 GetWeaponDisplayRateOfFire(const TESObjectWEAP& a_weapon, const TESObjectWEAP::InstanceData* a_data)
	{
		using FuncType = decltype(&CombatFormulas::GetWeaponDisplayRateOfFire);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::CombatFormulas::GetWeaponDisplayRateOfFire };
		return std::invoke(FUNC, a_weapon, a_data);
	}
}

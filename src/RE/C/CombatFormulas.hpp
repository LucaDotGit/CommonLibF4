#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/T/TESObjectWEAP.hpp"

namespace RE
{
	class BGSBodyPart;
}

namespace RE::CombatFormulas
{
	[[nodiscard]]
	auto CalcResistedPercentage(
		const ActorValueInfo& a_resistance,
		REX::Float32 a_damage,
		REX::Float32 a_resistancePoints) -> REX::Float32;
	[[nodiscard]]
	auto CalcScopeSteadyActionPointDrain(const Actor& a_actor, REX::Float32 a_deltaTime) -> REX::Float32;
	[[nodiscard]]
	auto CalcTargetedLimbDamage(
		const Actor& a_target,
		const BGSBodyPart& a_bodyPart,
		REX::Float32 a_physicalDamage,
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_damageTypes) -> REX::Float32;
	[[nodiscard]]
	auto CalcWeaponDamage(
		const TESForm* a_owner,
		const TESObjectWEAP::InstanceData* a_instanceData,
		const TESAmmo* a_ammo,
		REX::Float32 a_condition,
		REX::Float32 a_rangeMult) -> REX::Float32;
	[[nodiscard]]
	auto CalculateAimModelWobble(const Actor& a_actor) -> REX::Float64;
	[[nodiscard]]
	auto GetNumCrippledAttackConditions(const Actor& a_actor) -> std::int64_t;
	[[nodiscard]]
	auto GetWeaponDisplayAccuracy(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, Actor* a_actor) -> REX::Float32;
	[[nodiscard]]
	auto GetWeaponDisplayDamage(
		const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
		const TESAmmo* a_ammo,
		REX::Float32 a_condition) -> REX::Float32;
	[[nodiscard]]
	auto GetWeaponDisplayRange(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon) -> REX::Float32;
	[[nodiscard]]
	auto GetWeaponDisplayRateOfFire(const TESObjectWEAP& a_weapon, const TESObjectWEAP::InstanceData* a_data)
		-> REX::Float32;
}

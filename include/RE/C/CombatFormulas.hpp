#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/T/TESObjectWEAP.hpp"

namespace RE
{
	class BGSBodyPart;
}

namespace RE::CombatFormulas
{
	[[nodiscard]] REX::Float32 CalcResistedPercentage(const ActorValueInfo* a_resistance, REX::Float32 a_damage, REX::Float32 a_resistancePoints);
	[[nodiscard]] REX::Float32 CalcTargetedLimbDamage(Actor* a_target, const BGSBodyPart* a_bodyPart, REX::Float32 a_physicalDamage, BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* a_damageTypes);
	[[nodiscard]] REX::Float64 CalculateAimModelWobble(Actor* a_actor);
	[[nodiscard]] REX::Float32 CalcScopeSteadyActionPointDrain(Actor* a_actor, REX::Float32 a_deltaSec);
	[[nodiscard]] std::int64_t GetNumCrippledAttackConditions(Actor* a_actor);
	[[nodiscard]] REX::Float32 GetWeaponDisplayAccuracy(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, Actor* a_actor);
	[[nodiscard]] REX::Float32 GetWeaponDisplayDamage(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, const TESAmmo* a_ammo, REX::Float32 a_condition);
	[[nodiscard]] REX::Float32 GetWeaponDisplayRange(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon);
	[[nodiscard]] REX::Float32 GetWeaponDisplayRateOfFire(const TESObjectWEAP& a_weapon, const TESObjectWEAP::InstanceData* a_data);
}

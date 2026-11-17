#include "RE/A/Actor.hpp"

#include "RE/A/ACTOR_VISIBILITY_MASK.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/E/ExtraDataList.hpp" // IWYU pragma: keep
#include "RE/E/ExtraLeveledCreature.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESNPC.hpp"

namespace RE
{
	void Actor::AddPerk(BGSPerk* a_perk, std::uint8_t a_rank)
	{
		using FuncType = decltype(&Actor::AddPerk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::AddPerk);
		std::invoke(FUNC, this, a_perk, a_rank);
	}

	void Actor::CalculateDetectionFormula(Actor& a_target, DetectionData& a_detectionData)
	{
		using FuncType = decltype(&Actor::CalculateDetectionFormula);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::CalculateDetectionFormula);
		std::invoke(FUNC, this, a_target, a_detectionData);
	}

	auto Actor::CanUseIdle(TESIdleForm* a_idle) const -> bool
	{
		using FuncType = decltype(&Actor::CanUseIdle);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::CanUseIdle);
		return std::invoke(FUNC, this, a_idle);
	}

	void Actor::ClearAttackStates()
	{
		using FuncType = decltype(&Actor::ClearAttackStates);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::ClearAttackStates);
		std::invoke(FUNC, this);
	}

	void Actor::DoHitMe(const HitData* a_data)
	{
		using FuncType = decltype(&Actor::DoHitMe);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::DoHitMe);
		std::invoke(FUNC, this, a_data);
	}

	void Actor::EndInterruptPackage(bool a_notRunOnceDialogue)
	{
		using FuncType = decltype(&Actor::EndInterruptPackage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::EndInterruptPackage);
		std::invoke(FUNC, this, a_notRunOnceDialogue);
	}

	void Actor::ExitCover()
	{
		using FuncType = decltype(&Actor::ExitCover);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::ExitCover);
		std::invoke(FUNC, this);
	}

	void Actor::ForceDetect(Actor* a_target, bool a_forceLOS, REX::Float32 a_time)
	{
		using FuncType = decltype(&Actor::ForceDetect);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::ForceDetect);
		std::invoke(FUNC, this, a_target, a_forceLOS, a_time);
	}

	auto Actor::GetActorBase() const -> TESNPC*
	{
		auto* baseObject = GetBaseObject();
		return DynamicCast<TESNPC*>(baseObject);
	}

	auto Actor::GetActorHandle() const -> ActorHandle
	{
		return BSPointerHandleManagerInterface<Actor>::GetHandle(this);
	}

	void Actor::GetAimVector(NiPoint3& a_aimVector) const
	{
		using FuncType = decltype(&Actor::GetAimVector);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetAimVector);
		std::invoke(FUNC, this, a_aimVector);
	}

	auto Actor::GetBodyPartData() const -> BGSBodyPartData*
	{
		using FuncType = decltype(&Actor::GetBodyPartData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetBodyPartData);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetClosestBone(NiPoint3 a_impactLocation, NiPoint3 a_movementDirection) const -> NiAVObject*
	{
		using FuncType = decltype(&Actor::GetClosestBone);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetClosestBone);
		return std::invoke(FUNC, this, a_impactLocation, a_movementDirection);
	}

	auto Actor::GetCollisionFilter() const -> CFilter
	{
		using FuncType = decltype(&Actor::GetCollisionFilter);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetCollisionFilter);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetCombatStyle() const -> TESCombatStyle*
	{
		using FuncType = decltype(&Actor::GetCombatStyle);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetCombatStyle);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetCrimeTrackingFaction() const -> TESFaction*
	{
		using FuncType = decltype(&Actor::GetCrimeTrackingFaction);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetCrimeTrackingFaction);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetCurrentAmmo(BGSEquipIndex a_equipIndex) const -> TESAmmo*
	{
		return currentProcess ? currentProcess->GetCurrentAmmo(a_equipIndex) : nullptr;
	}

	auto Actor::GetCurrentAmmoCount(BGSEquipIndex a_equipIndex) const -> std::uint32_t
	{
		return currentProcess ? currentProcess->GetCurrentAmmoCount(a_equipIndex) : 0;
	}

	auto Actor::GetCurrentCollisionGroup() const -> std::uint32_t
	{
		using FuncType = decltype(&Actor::GetCurrentCollisionGroup);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetCurrentCollisionGroup);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetCurrentFireLocation(BGSEquipIndex a_index, NiPoint3& a_fireLocation) const -> bool
	{
		using FuncType = decltype(&Actor::GetCurrentFireLocation);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetCurrentFireLocation);
		return std::invoke(FUNC, this, a_index, a_fireLocation);
	}

	auto Actor::GetDesiredSpeed() const -> REX::Float32
	{
		using FuncType = decltype(&Actor::GetDesiredSpeed);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetDesiredSpeed);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetEquippedItem(BGSObjectInstance* a_result, BGSEquipIndex a_equipIndex) const -> BGSObjectInstance*
	{
		using FuncType = decltype(&Actor::GetEquippedItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetEquippedItem);
		return std::invoke(FUNC, this, a_result, a_equipIndex);
	}

	auto Actor::GetGhost() const -> bool
	{
		using FuncType = decltype(&Actor::GetGhost);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetGhost);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetHealthPercentage() -> REX::Float32
	{
		using FuncType = decltype(&Actor::GetHealthPercentage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetHealthPercentage);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetHostileToActor(Actor* a_actor) const -> bool
	{
		using FuncType = decltype(&Actor::GetHostileToActor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetHostileToActor);
		return std::invoke(FUNC, this, a_actor);
	}

	auto Actor::GetMobilityCrippled() const -> std::uint8_t
	{
		using FuncType = decltype(&Actor::GetMobilityCrippled);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetMobilityCrippled);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetMountHandle() const -> ActorHandle
	{
		using FuncType = decltype(&Actor::GetMountHandle);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetMountHandle);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetLevel() const -> std::int16_t
	{
		using FuncType = decltype(&Actor::GetLevel);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetLevel);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetOfferBarter() -> bool
	{
		using FuncType = decltype(&Actor::GetOfferBarter);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetOfferBarter);
		return std::invoke(FUNC, this);
	}

	auto Actor::GetPerkRank(BGSPerk* a_perk) const -> std::uint8_t
	{
		using FuncType = decltype(&Actor::GetPerkRank);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::GetPerkRank);
		return std::invoke(FUNC, this, a_perk);
	}

	auto Actor::GetSex() const -> SEX
	{
		const auto* actorBase = GetActorBase();
		return actorBase ? actorBase->GetSex() : SEX::None;
	}

	auto Actor::GetTemplateBase() const -> TESNPC*
	{
		const auto* leveledCreature = extraList->GetExtra<ExtraLeveledCreature>();
		if (leveledCreature) {
			return DynamicCast<TESNPC*>(leveledCreature->originalBase);
		}

		return GetActorBase();
	}

	void Actor::HandleDefaultAnimationSwitch()
	{
		using FuncType = decltype(&Actor::HandleDefaultAnimationSwitch);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::HandleDefaultAnimationSwitch);
		std::invoke(FUNC, this);
	}

	void Actor::HandleItemEquip(bool a_cullBone)
	{
		using FuncType = decltype(&Actor::HandleItemEquip);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::HandleItemEquip);
		std::invoke(FUNC, this, a_cullBone);
	}

	auto Actor::HasObjects(
		TESBoundObject* a_obj,
		PACKAGE_OBJECT_TYPE a_formID,
		std::int32_t a_number,
		std::uint32_t a_id,
		PACKAGE_OBJECT_TYPE& a_matchID) -> bool
	{
		using FuncType = decltype(&Actor::HasObjects);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::HasObjects);
		return std::invoke(FUNC, this, a_obj, a_formID, a_number, a_id, a_matchID);
	}

	void Actor::InitiateDoNothingPackage()
	{
		using FuncType = decltype(&Actor::InitiateDoNothingPackage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::InitiateDoNothingPackage);
		std::invoke(FUNC, this);
	}

	auto Actor::IsCrippled() const -> bool
	{
		using FuncType = decltype(&Actor::IsCrippled);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsCrippled);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsFollowing() const -> bool
	{
		using FuncType = decltype(&Actor::IsFollowing);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsFollowing);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsJumping() const -> bool
	{
		using FuncType = decltype(&Actor::IsJumping);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsJumping);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsPathValid() const -> bool
	{
		using FuncType = decltype(&Actor::IsPathValid);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsPathValid);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsPathing() const -> bool
	{
		using FuncType = decltype(&Actor::IsPathing);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsPathing);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsPathingComplete() const -> bool
	{
		using FuncType = decltype(&Actor::IsPathingComplete);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsPathingComplete);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsQuadruped() const -> bool
	{
		using FuncType = decltype(&Actor::IsQuadruped);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsQuadruped);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsSneaking() const -> bool
	{
		using FuncType = decltype(&Actor::IsSneaking);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::IsSneaking);
		return std::invoke(FUNC, this);
	}

	auto Actor::IsVisible() const -> bool
	{
		constexpr auto ALL_MASK = std::to_underlying(ACTOR_VISIBILITY_MASK::All);
		return ((visFlags & ALL_MASK) & 0xF) == ALL_MASK;
	}

	void Actor::Jump(REX::Float32 a_height)
	{
		using FuncType = decltype(&Actor::Jump);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::Jump);
		std::invoke(FUNC, this, a_height);
	}

	auto Actor::Move(REX::Float32 a_deltaTime, NiPoint3 a_deltaPos, bool a_defer) -> bhkCharacterController*
	{
		using FuncType = decltype(&Actor::Move);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::Move);
		return std::invoke(FUNC, this, a_deltaTime, a_deltaPos, a_defer);
	}

	auto Actor::PerformAction(BGSAction* a_action, TESObjectREFR* a_target) -> bool
	{
		using FuncType = decltype(&Actor::PerformAction);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::PerformAction);
		return std::invoke(FUNC, this, a_action, a_target);
	}

	auto Actor::PlaySoundByEditorName(
		BSSoundHandle& a_handle,
		const char* a_editorName,
		bool a_loop,
		std::uint32_t a_usageFlags) const -> BSSoundHandle
	{
		using FuncType = decltype(&Actor::PlaySoundByEditorName);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::PlaySoundByEditorName);
		return std::invoke(FUNC, this, a_handle, a_editorName, a_loop, a_usageFlags);
	}

	void Actor::RemovePerk(BGSPerk* a_perk)
	{
		using FuncType = decltype(&Actor::RemovePerk);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::RemovePerk);
		std::invoke(FUNC, this, a_perk);
	}

	void Actor::Reset3D(
		bool a_reloadAll,
		RESET_3D_FLAGS a_additionalFlags,
		bool a_queueReset,
		RESET_3D_FLAGS a_excludeFlags)
	{
		using FuncType = decltype(&Actor::Reset3D);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::Reset3D);
		std::invoke(FUNC, this, a_reloadAll, a_additionalFlags, a_queueReset, a_excludeFlags);
	}

	void Actor::RewardExperience(
		REX::Float32 a_amount,
		bool a_direct,
		TESObjectREFR* a_actionTarget,
		TESObjectREFR* a_killWeapon)
	{
		using FuncType = decltype(&Actor::RewardExperience);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::RewardExperience);
		std::invoke(FUNC, this, a_amount, a_direct, a_actionTarget, a_killWeapon);
	}

	void Actor::StopAttack(BGSEquipIndex a_equipIndex)
	{
		using FuncType = decltype(&Actor::StopAttack);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::StopAttack);
		std::invoke(FUNC, this, a_equipIndex);
	}

	void Actor::SPECIALModifiedCallback(
		const ActorValueInfo* a_info,
		REX::Float32 a_originalValue,
		REX::Float32 a_delta)
	{
		using FuncType = decltype(&Actor::SPECIALModifiedCallback);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::SPECIALModifiedCallback);
		std::invoke(FUNC, this, a_info, a_originalValue, a_delta);
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	void Actor::SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
	{
		if (currentProcess) {
			currentProcess->SetCurrentAmmo(a_equipIndex, a_ammo);
		}
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	void Actor::SetCurrentAmmoCount(BGSEquipIndex a_equipIndex, std::uint32_t a_count)
	{
		if (currentProcess) {
			currentProcess->SetCurrentAmmoCount(a_equipIndex, a_count);
		}
	}

	void Actor::SetGunState(GUN_STATE a_gunState, bool a_set)
	{
		using FuncType = decltype(&Actor::SetGunState);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::SetGunState);
		std::invoke(FUNC, this, a_gunState, a_set);
	}

	void Actor::SetHeading(REX::Float32 a_angle)
	{
		using FuncType = decltype(&Actor::SetHeading);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::SetHeading);
		std::invoke(FUNC, this, a_angle);
	}

	void Actor::StopInteractingQuick(bool a_instance, bool a_moveActor, bool a_update3D)
	{
		using FuncType = decltype(&Actor::StopInteractingQuick);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::StopInteractingQuick);
		std::invoke(FUNC, this, a_instance, a_moveActor, a_update3D);
	}

	void Actor::TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_owner, std::int32_t a_crime)
	{
		using FuncType = decltype(&Actor::TrespassAlarm);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::TrespassAlarm);
		std::invoke(FUNC, this, a_ref, a_owner, a_crime);
	}

	void Actor::UnequipObject(TESBoundObject* a_object, ObjectEquipParams a_params)
	{
		using FuncType = decltype(&Actor::UnequipObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::UnequipObject);
		std::invoke(FUNC, this, a_object, a_params);
	}

	void Actor::UpdateSprinting()
	{
		using FuncType = decltype(&Actor::UpdateSprinting);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::UpdateSprinting);
		std::invoke(FUNC, this);
	}

	void Actor::UpdateVoiceTimer(bool a_force)
	{
		using FuncType = decltype(&Actor::UpdateVoiceTimer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Actor::UpdateVoiceTimer);
		std::invoke(FUNC, this, a_force);
	}
}

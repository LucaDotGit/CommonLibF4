#pragma once

#include "RE/A/AIProcess.hpp"
#include "RE/A/AITimeStamp.hpp"
#include "RE/A/ActorState.hpp"
#include "RE/A/ActorValueStorage.hpp"
#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSNonReentrantSpinLock.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSPointerHandleSmartPointer.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CFilter.hpp"
#include "RE/I/IPostAnimationChannelUpdateFunctor.hpp"
#include "RE/M/MagicTarget.hpp"
#include "RE/M/Modifiers.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/O/ObjectEquipParams.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::MagicSystem
{
	enum class CannotCastReason : std::int32_t;
}

namespace RE::PerkValueEvents
{
	class PerkEntryUpdatedEvent;
	class PerkValueChangedEvent;
}

namespace RE
{
	enum class ACTOR_CRITICAL_STAGE : std::int32_t;
	enum class ACTOR_LIFE_STATE : std::uint32_t;
	enum class ACTOR_LOS_LOCATION : std::int32_t;
	enum class GUN_STATE : std::uint32_t;
	enum class PACKAGE_OBJECT_TYPE : std::int32_t;
	enum class POWER_ATTACK_TYPE : std::int32_t;
	enum class RESET_3D_FLAGS : std::int32_t;
	enum class SEX : std::int32_t;

	class ActorCPMEvent;
	class ActorMagicCaster;
	class ActorMotionFeedbackData;
	class ActorMotionFeedbackOutput;
	class ActorMover;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class bhkCharacterStateChangeEvent;
	class bhkNonSupportContactEvent;
	class BSMovementDataChangedEvent;
	class BSSoundHandle;
	class BSSubGraphActivationUpdate;
	class BSTransformDeltaEvent;
	class CastPowerItem;
	class CombatController;
	class CombatGroup;
	class DetectionData;
	class HitData;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class MovementMessageNewPath;
	class MovementMessageUpdateRequestImmediate;
	class PackageLocation;
	class PerkEntryVisitor;
	class Perks;

	class __declspec(novtable) Actor :
		public TESObjectREFR,										   // 0x000
		public MagicTarget,											   // 0x110
		public ActorState,											   // 0x128
		public BSTEventSink<BSMovementDataChangedEvent>,			   // 0x138
		public BSTEventSink<BSTransformDeltaEvent>,					   // 0x140
		public BSTEventSink<BSSubGraphActivationUpdate>,			   // 0x148
		public BSTEventSink<bhkCharacterMoveFinishEvent>,			   // 0x150
		public BSTEventSink<bhkNonSupportContactEvent>,				   // 0x158
		public BSTEventSink<bhkCharacterStateChangeEvent>,			   // 0x160
		public IPostAnimationChannelUpdateFunctor,					   // 0x168
		public BSTEventSource<MovementMessageUpdateRequestImmediate>,  // 0x170
		public BSTEventSource<PerkValueEvents::PerkValueChangedEvent>, // 0x1C8
		public BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>, // 0x220
		public BSTEventSource<ActorCPMEvent>						   // 0x278
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Actor;
		inline static constexpr const auto& VTABLE = VTABLE::Actor;
		inline static constexpr auto FORM_TYPE = FormType::Actor;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				LifeState = 1 << 10,
				ExtraPackageData = 1 << 11,
				ExtraMerchantContainer = 1 << 12,
				ExtraDismemberedLimbs = 1 << 17,
				ExtraLeveledActor = 1 << 18,
				DispositionModifiers = 1 << 19,
				TempModifiers = 1 << 20,
				DamageModifiers = 1 << 21,
				OverrideModifiers = 1 << 22,
				PermanentModifiers = 1 << 23
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class NiFlags : std::uint32_t
		{
			None = 0,
			DelayUpdateScenegraph = 1 << 0,
			ProcessMe = 1 << 1,
			MurderAlarm = 1 << 2,
			HasSceneExtra = 1 << 3,
			HeadingFixed = 1 << 4,
			SpeakingDone = 1 << 5,
			IgnoreChangeAnimationCall = 1 << 6,
			SoundFileDone = 1 << 7,
			VoiceFileDone = 1 << 8,
			InTempChangeList = 1 << 9,
			DoNotRunSayToCallback = 1 << 10,
			Dead = 1 << 11,
			ForceGreetingPlayer = 1 << 12,
			ForceUpdateQuestTarget = 1 << 13,
			SearchingInCombat = 1 << 14,
			AttackOnNextTheft = 1 << 15,
			EvpBuffered = 1 << 16,
			ResetAI = 1 << 17,
			InWater = 1 << 18,
			Swimming = 1 << 19,
			VoicePausedByScript = 1 << 20,
			WasInFrustum = 1 << 21,
			ShouldRotateToTrack = 1 << 22,
			SetOnDeath = 1 << 23,
			DoNotPadVoice = 1 << 24,
			FootIKInRange = 1 << 25,
			PlayerTeammate = 1 << 26,
			GivePlayerXP = 1 << 27,
			SoundCallbackSuccess = 1 << 28,
			UseEmotion = 1 << 29,
			Guard = 1 << 30,
			Paralyzed = static_cast<std::uint32_t>(1) << 31
		};

		enum class BOOL_FLAGS : std::uint32_t
		{
			None = 0,
			ScenePackage = 1 << 0,
			IsAMount = 1 << 1,
			IsMountPointClear = 1 << 2,
			IsGettingOnOffMount = 1 << 3,
			InRandomScene = 1 << 4,
			NoBleedoutRecovery = 1 << 5,
			InBleedoutAnimation = 1 << 6,
			CanDoFavor = 1 << 7,
			ShouldAnimGraphUpdate = 1 << 8,
			CanSpeakToEssentialDown = 1 << 9,
			BribedByPlayer = 1 << 10,
			AngryWithPlayer = 1 << 11,
			IsTrespassing = 1 << 12,
			CanSpeak = 1 << 13,
			IsInKillMove = 1 << 14,
			AttackOnSight = 1 << 15,
			IsCommandedActor = 1 << 16,
			ForceOneAnimGraphUpdate = 1 << 17,
			Essential = 1 << 18,
			Protected = 1 << 19,
			AttackingDisabled = 1 << 20,
			CastingDisabled = 1 << 21,
			SceneHeadtrackRotation = 1 << 22,
			ForceIncMinBoneUpdate = 1 << 23,
			CrimeSearch = 1 << 24,
			MovingIntoLoadedArea = 1 << 25,
			DoNotShowOnStealthMeter = 1 << 26,
			MovementBlocked = 1 << 27,
			AllowInstantFurniturePopInPlayerCell = 1 << 28,
			ForceAnimGraphUpdate = 1 << 29,
			CheckAddEffectDualCast = 1 << 30,
			Underwater = static_cast<std::uint32_t>(1) << 31
		};

		enum class BOOL_FLAGS2 : std::uint32_t
		{
			None = 0,
			SayingHello = 1 << 0,
			EndResultRun = 1 << 1,
			EvpBufferedUntil3DLoaded = 1 << 2,
			InDialogueScenePlayer = 1 << 3,
			HasHoldPackageScene = 1 << 4,
			ChargenSkeleton = 1 << 5,
			HasInfoStartSceneRun = 1 << 6,
			FadingVoice = 1 << 7,
			DisableNonCombatHealRateBonus = 1 << 8,
			OnlyRunScenePackage = 1 << 9,
			DisableQueued = 1 << 10,
			OnWaterNavMesh = 1 << 11,
			SkipInventoryReset = 1 << 12,
			NoCommandSceneState = 1 << 13,
			EvalSceneStopCombat = 1 << 14,

			SaveMask = 0x0'FFFF'FFDF
		};

		~Actor() override; // 0x00

		// add
		virtual void PlayPickUpSound(TESBoundObject* a_boundObj, bool a_pickUp, bool a_use); // 0x0C6
		virtual auto GetHeading() const -> REX::Float32; // 0x0C7 - { return data.angle.z; }
		virtual void SetAvoidanceDisabled(bool a_tf);	 // 0x0C8 - { return; }
		virtual void DrawWeaponMagicHands(bool a_draw);	 // 0x0C9
		virtual void SetPosition(const NiPoint3& a_position, bool a_updateCharController);					// 0x0CA
		virtual void KillDying();																			// 0x0CB
		virtual void Resurrect(bool a_resetInventory, bool a_attach3D);										// 0x0CC
		virtual auto PutActorInChairBedQuick(TESObjectREFR* a_furniture, std::uint32_t a_index) -> bool;	// 0x0CD
		virtual auto PutActorOnMountQuick() -> bool;														// 0x0CE
		virtual void Update(REX::Float32 a_deltaTime);														// 0x0CF
		virtual void UpdateNoAI(REX::Float32 a_deltaTime);													// 0x0D0
		virtual void UpdateMotionDrivenState();																// 0x0D1
		virtual void UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_charController); // 0x0D2
		virtual void PotentiallyFixRagdollState();															// 0x0D3
		virtual void UpdateNonRenderSafe(REX::Float32);														// 0x0D4
		virtual auto ShouldHandleEquipNow() const -> bool;													// 0x0D5
		virtual void SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_value);		// 0x0D6
		virtual auto ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value)
			-> std::uint32_t;																			// 0x0D7
		virtual void RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value); // 0x0D8
		virtual auto GetCrimeGoldValue(const TESFaction* a_faction) const -> std::uint32_t;				// 0x0D9
		virtual void GoToPrison(TESFaction* a_faction, bool a_removeItems, bool a_realJail); // 0x0DA - { return; }
		virtual void ServePrisonTime();														 // 0x0DB - { return; }
		virtual void PayFine(
			TESFaction* a_faction,
			bool a_movetoMarker,
			bool a_removeStolenItems);							 // 0x0DC - { return; }
		virtual auto GetCurrentEyeLevel() const -> REX::Float32; // 0x0DD
		virtual void SetInDialogueWithPlayer(bool a_set);		 // 0x0DE
		virtual auto GetCannibal() -> bool;						 // 0x0DF - { return false; }
		virtual void SetCannibal(bool);							 // 0x0E0 - { return; }
		virtual auto GetVampireFeed() -> bool;					 // 0x0E1 - { return false; }
		virtual void SetVampireFeed(bool);						 // 0x0E2 - { return; }
		virtual void InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);					// 0x0E3
		virtual void InitiateCannibalPackage(Actor* a_target);													// 0x0E4
		virtual auto GetEyeHeading() const -> REX::Float32;														// 0x0E5
		virtual void GetEyeAngles(REX::Float32& a_eyeHeading, REX::Float32& a_eyeLooking) const;				// 0x0E6
		virtual void GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset) const; // 0x0E7
		virtual void SetRefraction(bool a_enable, REX::Float32 a_refractionPower);								// 0x0E8
		virtual auto GetAcrobatics() const -> REX::Float32; // 0x0E9 - { return static_cast<REX::Float32>(1.0); }
		virtual auto Get3DUpdateFlag(RESET_3D_FLAGS a_flags) const -> bool; // 0x0EA
		virtual auto DropObject(
			const BGSObjectInstance& a_object,
			BSTSmallArray<std::uint32_t, 4>* a_stackData,
			std::int32_t a_number,
			const NiPoint3* a_point,
			const NiPoint3* a_rotate) -> ObjectRefHandle;													// 0x0EB
		virtual void PickUpObject(TESObjectREFR* a_objREFR, std::int32_t a_count, bool a_playPickUpSounds); // 0x0EC
		virtual void AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);	// 0x0ED
		virtual void DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);	// 0x0EE
		virtual auto ReloadWeapon(
			const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
			BGSEquipIndex a_equipIndex) -> bool; // 0x0EF
		virtual auto UseAmmo(
			const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
			BGSEquipIndex a_equipIndex,
			std::uint32_t a_shotCount) -> std::uint32_t;					   // 0x0F0
		virtual auto CalculateCachedOwnerIsInCombatantFaction() const -> bool; // 0x0F1
		virtual auto GetCombatGroup() const -> CombatGroup*;				   // 0x0F2
		virtual void SetCombatGroup(CombatGroup* a_group);					   // 0x0F3
		virtual auto CheckValidTarget(TESObjectREFR& a_ref) const -> bool;	   // 0x0F4
		virtual auto InitiateDialogue(
			Actor* a_target,
			PackageLocation* a_packLoc,
			PackageLocation* a_packSecondLoc) -> bool;													// 0x0F5
		virtual void EndDialogue();																		// 0x0F6
		virtual auto SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_talkingActivator) -> Actor*; // 0x0F7
		virtual void InitiateFlee(
			TESObjectREFR* a_fleeRef,
			bool a_runonce,
			bool a_knows,
			bool a_combatMode,
			TESObjectCELL* a_cell,
			TESObjectREFR* a_ref,
			REX::Float32 a_fleeFromDist,
			REX::Float32 a_fleeToDist);		 // 0x0F8
		virtual void InitiateGetUpPackage(); // 0x0F9
		virtual void PutCreatedPackage(
			TESPackage* a_pack,
			bool a_tempPack,
			bool a_isACreatedPackage,
			bool a_allowFromFurniture);										   // 0x0FA
		virtual void UpdateAlpha();											   // 0x0FB
		virtual void SetAlpha(REX::Float32 a_newAlpha);						   // 0x0FC
		virtual auto GetAlpha() -> REX::Float32;							   // 0x0FD
		virtual auto IsInCombat() const -> bool;							   // 0x0FE
		virtual void UpdateCombat();										   // 0x0FF
		virtual void StopCombat();											   // 0x100
		virtual auto GetUsesAttackPercents() -> bool;						   // 0x101 - { return false; }
		virtual auto GetPowerAttackPercent(POWER_ATTACK_TYPE) -> std::uint8_t; // 0x102 - { return 0; }
		virtual void WeaponSwingCallBack(BGSEquipIndex a_equipIndex);		   // 0x103
		virtual void SetActorStartingPosition();							   // 0x104
		virtual void SetLifeState(ACTOR_LIFE_STATE a_lifeState);			   // 0x105
		virtual auto HasBeenAttacked() -> bool;								   // 0x106
		virtual void SetBeenAttacked(bool a_set);							   // 0x107
		virtual void UseSkill(ActorValueInfo*, REX::Float32, TESForm*);		   // 0x108 - { return; }
		virtual auto IsAtPoint(
			const NiPoint3& a_point,
			REX::Float32 a_radius,
			bool a_expandRadius,
			bool a_alwaysTestHeight) -> bool;														 // 0x109
		virtual auto IsInFaction(const TESFaction* a_faction) const -> bool;						 // 0x10A
		virtual auto HasPerkEntries(std::uint8_t a_entryPoint) const -> bool;						 // 0x10B
		virtual void ForEachPerkEntry(std::uint8_t a_entryPoint, PerkEntryVisitor& a_visitor) const; // 0x10C
		virtual void ApplyPerksFromBase();															 // 0x10D
		virtual void StartPowerAttackCoolDown();											// 0x10E - { return; }
		virtual auto IsPowerAttackCoolingDown() const -> bool;								// 0x10F - { return false; }
		virtual void HandleHealthDamage(Actor* a_attacker, REX::Float32 a_damage);			// 0x110
		virtual auto QSpeakingDone() const -> bool;											// 0x111
		virtual void SetSpeakingDone(bool a_done);											// 0x112
		virtual auto CalculateLOSLocation(ACTOR_LOS_LOCATION a_location) const -> NiPoint3; // 0x113
		virtual void CreateMovementController();											// 0x114
		virtual auto ShouldPivotToFaceCamera() const -> bool;								// 0x115 - { return false; }
		virtual auto GetSpeakingAnimArchType() -> BGSKeyword*; // 0x116 - { return speakingAnimArchType; }
		virtual void KillImpl(
			Actor* a_attacker,
			REX::Float32 a_damage,
			bool a_sendEvent,
			bool a_ragdollInstant); // 0x117
		virtual void DoReparentWeapon(
			const TESObjectWEAP* a_weapon,
			BGSEquipIndex a_equipIndex,
			bool a_weaponDrawn);														  // 0x118
		virtual auto DrinkPotion(AlchemyItem* a_potion, std::uint32_t a_stackID) -> bool; // 0x119
		virtual auto CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason)
			-> bool;													// 0x11A
		virtual void CheckTempModifiers();								// 0x11B - { return; }
		virtual void SetLastRiddenMount(ActorHandle a_mount);			// 0x11C - { return; }
		virtual auto QLastRiddenMount() const -> ActorHandle;			// 0x11D
		virtual auto CalculateCachedOwnerIsUndead() const -> bool;		// 0x11E
		virtual auto CalculateCachedOwnerIsNPC() const -> bool;			// 0x11F
		virtual auto SetSneaking(bool a_sneaking) -> bool;				// 0x120
		virtual void ResetHavokPhysics();								// 0x121
		virtual auto ShouldDoCharacterUpdate() const -> bool;			// 0x122 - { return true; }
		virtual auto GetAnimationCanBeInterpolated() const -> bool;		// 0x123
		virtual auto GetResponseString() const -> const BSFixedString&; // 0x124
		virtual void ModifyMovementData(REX::Float32 a_delta, NiPoint3& a_moveDelta, NiPoint3& a_angleDelta); // 0x125
		virtual void UpdateCombatControllerSettings();														  // 0x126
		virtual void UpdateFadeSettings(bhkCharacterController* a_charController);							  // 0x127
		virtual auto ComputeMotionFeedbackSpeedAndDirection(
			const ActorMotionFeedbackData& a_data,
			REX::Float32 a_delta,
			ActorMotionFeedbackOutput& a_retData) -> bool;													// 0x128
		virtual auto UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_data) -> bool; // 0x129
		virtual void UpdateActor3DPosition();																// 0x12A
		virtual void PrecacheData();																		// 0x12B
		virtual void WornArmorChanged(const BGSObjectInstance& a_object);									// 0x12C
		virtual void ProcessTracking(REX::Float32 a_delta, NiAVObject* a_ob3D);								// 0x12D
		virtual void CreateActorMover();																	// 0x12E
		virtual void DestroyActorMover();																	// 0x12F
		virtual auto ShouldRespondToActorCollision(
			const MovementMessageActorCollision&,
			const ActorHandlePtr& a_otherActor) const -> bool;												 // 0x130
		virtual auto CheckClampDamageModifier(ActorValueInfo& a_info, REX::Float32 a_delta) -> REX::Float32; // 0x131
		virtual void ValidateNewPath(const MovementMessageNewPath& a_newPathMessage); // 0x132 - { return; }

		void AddPerk(BGSPerk* a_perk, std::uint8_t a_rank = 0);
		void CalculateDetectionFormula(Actor& a_target, DetectionData& a_detectionData);
		[[nodiscard]]
		auto CanUseIdle(TESIdleForm* a_idle) const -> bool;
		void ClearAttackStates();
		void DoHitMe(const HitData* a_data);
		void EndInterruptPackage(bool a_notRunOnceDialogue);
		void ExitCover();
		void ForceDetect(Actor* a_target, bool a_forceLOS, REX::Float32 a_time);
		[[nodiscard]]
		auto GetActorBase() const -> TESNPC*;
		[[nodiscard]]
		auto GetActorHandle() const -> ActorHandle;
		void GetAimVector(NiPoint3& a_aimVector) const;
		[[nodiscard]]
		auto GetBodyPartData() const -> BGSBodyPartData*;
		[[nodiscard]]
		auto GetClosestBone(NiPoint3 a_impactLocation, NiPoint3 a_movementDirection) const -> NiAVObject*;
		[[nodiscard]]
		auto GetCollisionFilter() const -> CFilter;
		[[nodiscard]]
		auto GetCombatStyle() const -> TESCombatStyle*;
		[[nodiscard]]
		auto GetCrimeTrackingFaction() const -> TESFaction*;
		[[nodiscard]]
		auto GetCurrentAmmo(BGSEquipIndex a_equipIndex) const -> TESAmmo*;
		[[nodiscard]]
		auto GetCurrentAmmoCount(BGSEquipIndex a_equipIndex) const -> std::uint32_t;
		[[nodiscard]]
		auto GetCurrentCollisionGroup() const -> std::uint32_t;
		[[nodiscard]]
		auto GetCurrentFireLocation(BGSEquipIndex a_index, NiPoint3& a_fireLocation) const -> bool;
		[[nodiscard]]
		auto GetDesiredSpeed() const -> REX::Float32;
		[[nodiscard]]
		auto GetEquippedItem(BGSObjectInstance* a_result, BGSEquipIndex a_equipIndex) const -> BGSObjectInstance*;
		[[nodiscard]]
		auto GetEquippedItemHealth(BGSEquipIndex a_equipIndex) const -> REX::Float32;
		[[nodiscard]]
		auto GetGhost() const -> bool;
		[[nodiscard]]
		auto GetHealthPercentage() -> REX::Float32;
		[[nodiscard]]
		auto GetHostileToActor(Actor* a_actor) const -> bool;
		[[nodiscard]]
		auto GetMobilityCrippled() const -> std::uint8_t;
		[[nodiscard]]
		auto GetMountHandle() const -> ActorHandle;
		[[nodiscard]]
		auto GetLevel() const -> std::int16_t;
		[[nodiscard]]
		auto GetOfferBarter() -> bool;
		[[nodiscard]]
		auto GetPerkRank(BGSPerk* a_perk) const -> std::uint8_t;
		[[nodiscard]]
		auto GetSex() const -> SEX;
		[[nodiscard]]
		auto GetTemplateBase() const -> TESNPC*;
		void HandleDefaultAnimationSwitch();
		void HandleItemEquip(bool a_cullBone);
		auto HasObjects(
			TESBoundObject* a_obj,
			PACKAGE_OBJECT_TYPE a_formID,
			std::int32_t a_number,
			std::uint32_t a_id,
			PACKAGE_OBJECT_TYPE& a_matchID) -> bool;
		void InitiateDoNothingPackage();
		[[nodiscard]]
		auto IsCrippled() const -> bool;
		[[nodiscard]]
		auto IsFollowing() const -> bool;
		[[nodiscard]]
		auto IsJumping() const -> bool;
		[[nodiscard]]
		auto IsPathValid() const -> bool;
		[[nodiscard]]
		auto IsPathing() const -> bool;
		[[nodiscard]]
		auto IsPathingComplete() const -> bool;
		[[nodiscard]]
		auto IsQuadruped() const -> bool;
		[[nodiscard]]
		auto IsSneaking() const -> bool;
		[[nodiscard]]
		auto IsVisible() const -> bool;
		void Jump(REX::Float32 a_height);
		auto Move(REX::Float32 a_deltaTime, NiPoint3 a_deltaPos, bool a_defer) -> bhkCharacterController*;
		auto PerformAction(BGSAction* a_action, TESObjectREFR* a_target) -> bool;
		auto PlaySoundByEditorName(
			BSSoundHandle& a_handle,
			const char* a_editorName,
			bool a_loop,
			std::uint32_t a_usageFlags) const -> BSSoundHandle;
		void RemovePerk(BGSPerk* a_perk);
		void Reset3D(
			bool a_reloadAll,
			RESET_3D_FLAGS a_additionalFlags,
			bool a_queueReset,
			RESET_3D_FLAGS a_excludeFlags);
		void RewardExperience(
			REX::Float32 a_amount,
			bool a_direct,
			TESObjectREFR* a_actionTarget,
			TESObjectREFR* a_killWeapon);
		void StopAttack(BGSEquipIndex a_equipIndex);
		void SPECIALModifiedCallback(const ActorValueInfo* a_info, REX::Float32 a_originalValue, REX::Float32 a_delta);
		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo);
		void SetCurrentAmmoCount(BGSEquipIndex a_equipIndex, std::uint32_t a_count);
		void SetGunState(GUN_STATE a_gunState, bool a_set);
		void SetHeading(REX::Float32 a_angle);
		void StopInteractingQuick(bool a_instance, bool a_moveActor, bool a_update3D);
		void TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_owner, std::int32_t a_crime);
		void UnequipObject(TESBoundObject* a_object, ObjectEquipParams a_params);
		void UpdateSprinting();
		void UpdateVoiceTimer(bool a_force);

		// members
		REX::EnumSet<NiFlags, std::uint32_t> niFlags;				 // 0x2D0
		REX::Float32 updateTargetTimer;								 // 0x2D4
		NiPoint3 editorLocCoord;									 // 0x2D8
		NiPoint3 editorLocRot;										 // 0x2E4
		TESForm* editorLocForm;										 // 0x2F0
		BGSLocation* editorLocation;								 // 0x2F8
		AIProcess* currentProcess;									 // 0x300
		ActorMover* actorMover;										 // 0x308
		BGSKeyword* speakingAnimArchType;							 // 0x310
		BSTSmartPointer<MovementControllerNPC> movementController;	 // 0x318
		TESPackage* initialPackage;									 // 0x320
		CombatController* combatController;							 // 0x328
		TESFaction* vendorFaction;									 // 0x330
		ActorValueStorage avStorage;								 // 0x338
		BGSDialogueBranch* exclusiveBranch;							 // 0x370
		REX::Enum<ACTOR_CRITICAL_STAGE, std::int32_t> criticalStage; // 0x378
		ObjectRefHandle dialogueItemTarget;							 // 0x37C
		ActorHandle currentCombatTarget;							 // 0x380
		ActorHandle myKiller;										 // 0x384
		REX::Float32 checkMyDeadBodyTimer;							 // 0x388
		REX::Float32 voiceTimer;									 // 0x38C
		REX::Float32 voiceLengthTotal;								 // 0x390
		REX::Float32 underWaterTimer;								 // 0x394
		std::int32_t thiefCrimeStamp;								 // 0x398
		std::int32_t actionValue;									 // 0x39C
		REX::Float32 timerOnAction;									 // 0x3A0
		AITimeStamp calculateVendorFactionTimer;					 // 0x3A4
		std::uint32_t intimidateBribeDayStamp;						 // 0x3A8
		REX::Float32 equippedWeight;								 // 0x3AC
		BSTSmallArray<SpellItem*> addedSpells;						 // 0x3B0
		std::array<ActorMagicCaster*, 4> magicCasters;				 // 0x3C8
		std::array<MagicItem*, 4> selectedSpell;					 // 0x3E8
		CastPowerItem* castPowerItems;								 // 0x408
		TESForm* selectedPower;										 // 0x410
		TESRace* race;												 // 0x418
		Perks* perks;												 // 0x420
		BSTSmartPointer<BipedAnim> biped;							 // 0x428
		mutable BSNonReentrantSpinLock addingToOrRemovingFromScene;	 // 0x430
		mutable BSReadWriteLock perkArrayLock;						 // 0x434
		REX::EnumSet<BOOL_FLAGS, std::uint32_t> boolFlags;			 // 0x43C
		std::uint32_t moreFlags;									 // 0x440
		Modifiers healthModifiers;									 // 0x444
		Modifiers actionPointsModifiers;							 // 0x450
		Modifiers staminaModifiers;									 // 0x45C
		Modifiers radsModifiers;									 // 0x468
		REX::Float32 lastUpdate;									 // 0x474
		std::uint32_t lastSeenTime;									 // 0x478
		REX::Float32 armorRating;									 // 0x47C
		REX::Float32 armorBaseFactorSum;							 // 0x480
		std::uint32_t visFlags			: 4;						 // 0x484:00
		std::uint32_t raceSwitchPending : 1;						 // 0x488:0
		std::int8_t soundCallBackSet;								 // 0x489
		bool trespassing;											 // 0x48A
	};

	static_assert(sizeof(Actor) == 0x490);
}

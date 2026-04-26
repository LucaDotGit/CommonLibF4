#pragma once

#include "RE/A/AIProcess.hpp"
#include "RE/A/AITimeStamp.hpp"
#include "RE/A/ActorState.hpp"
#include "RE/A/ActorValueStorage.hpp"
#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSPointerHandleSmartPointer.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CFilter.hpp"
#include "RE/I/IPostAnimationChannelUpdateFunctor.hpp"
#include "RE/M/MagicTarget.hpp"
#include "RE/M/Modifiers.hpp"
#include "RE/N/NiPoint.hpp"
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
	class BSSubGraphActivationUpdate;
	class BSTransformDeltaEvent;
	class CastPowerItem;
	class CombatController;
	class CombatGroup;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class MovementMessageNewPath;
	class MovementMessageUpdateRequestImmediate;
	class PackageLocation;
	class PerkEntryVisitor;
	class Perks;

	class __declspec(novtable) Actor
		: public TESObjectREFR,											 // 000
		  public MagicTarget,											 // 110
		  public ActorState,											 // 128
		  public BSTEventSink<BSMovementDataChangedEvent>,				 // 138
		  public BSTEventSink<BSTransformDeltaEvent>,					 // 140
		  public BSTEventSink<BSSubGraphActivationUpdate>,				 // 148
		  public BSTEventSink<bhkCharacterMoveFinishEvent>,				 // 150
		  public BSTEventSink<bhkNonSupportContactEvent>,				 // 158
		  public BSTEventSink<bhkCharacterStateChangeEvent>,			 // 160
		  public IPostAnimationChannelUpdateFunctor,					 // 168
		  public BSTEventSource<MovementMessageUpdateRequestImmediate>,	 // 170
		  public BSTEventSource<PerkValueEvents::PerkValueChangedEvent>, // 1C8
		  public BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>, // 220
		  public BSTEventSource<ActorCPMEvent>							 // 278
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Actor };
		inline static constexpr auto VTABLE{ VTABLE::Actor };
		inline static constexpr auto FORM_TYPE{ FormType::kActor };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kLifeState = 1 << 10,
				kExtraPackageData = 1 << 11,
				kExtraMerchantContainer = 1 << 12,
				kExtraDismemberedLimbs = 1 << 17,
				kExtraLeveledActor = 1 << 18,
				kDispositionModifiers = 1 << 19,
				kTempModifiers = 1 << 20,
				kDamageModifiers = 1 << 21,
				kOverrideModifiers = 1 << 22,
				kPermanentModifiers = 1 << 23
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class NiFlags : std::uint32_t
		{
			kNone = 0,
			kDelayUpdateScenegraph = 1 << 0,
			kProcessMe = 1 << 1,
			kMurderAlarm = 1 << 2,
			kHasSceneExtra = 1 << 3,
			kHeadingFixed = 1 << 4,
			kSpeakingDone = 1 << 5,
			kIgnoreChangeAnimationCall = 1 << 6,
			kSoundFileDone = 1 << 7,
			kVoiceFileDone = 1 << 8,
			kInTempChangeList = 1 << 9,
			kDoNotRunSayToCallback = 1 << 10,
			kDead = 1 << 11,
			kForceGreetingPlayer = 1 << 12,
			kForceUpdateQuestTarget = 1 << 13,
			kSearchingInCombat = 1 << 14,
			kAttackOnNextTheft = 1 << 15,
			kEvpBuffered = 1 << 16,
			kResetAI = 1 << 17,
			kInWater = 1 << 18,
			kSwimming = 1 << 19,
			kVoicePausedByScript = 1 << 20,
			kWasInFrustum = 1 << 21,
			kShouldRotateToTrack = 1 << 22,
			kSetOnDeath = 1 << 23,
			kDoNotPadVoice = 1 << 24,
			kFootIKInRange = 1 << 25,
			kPlayerTeammate = 1 << 26,
			kGivePlayerXP = 1 << 27,
			kSoundCallbackSuccess = 1 << 28,
			kUseEmotion = 1 << 29,
			kGuard = 1 << 30,
			kParalyzed = 1ui32 << 31
		};

		enum class BOOL_FLAGS : std::uint32_t
		{
			kNone = 0,
			kScenePackage = 1 << 0,
			kIsAMount = 1 << 1,
			kIsMountPointClear = 1 << 2,
			kIsGettingOnOffMount = 1 << 3,
			kInRandomScene = 1 << 4,
			kNoBleedoutRecovery = 1 << 5,
			kInBleedoutAnimation = 1 << 6,
			kCanDoFavor = 1 << 7,
			kShouldAnimGraphUpdate = 1 << 8,
			kCanSpeakToEssentialDown = 1 << 9,
			kBribedByPlayer = 1 << 10,
			kAngryWithPlayer = 1 << 11,
			kIsTrespassing = 1 << 12,
			kCanSpeak = 1 << 13,
			kIsInKillMove = 1 << 14,
			kAttackOnSight = 1 << 15,
			kIsCommandedActor = 1 << 16,
			kForceOneAnimGraphUpdate = 1 << 17,
			kEssential = 1 << 18,
			kProtected = 1 << 19,
			kAttackingDisabled = 1 << 20,
			kCastingDisabled = 1 << 21,
			kSceneHeadtrackRotation = 1 << 22,
			kForceIncMinBoneUpdate = 1 << 23,
			kCrimeSearch = 1 << 24,
			kMovingIntoLoadedArea = 1 << 25,
			kDoNotShowOnStealthMeter = 1 << 26,
			kMovementBlocked = 1 << 27,
			kAllowInstantFurniturePopInPlayerCell = 1 << 28,
			kForceAnimGraphUpdate = 1 << 29,
			kCheckAddEffectDualCast = 1 << 30,
			kUnderwater = 1ui32 << 31
		};

		enum class BOOL_FLAGS2 : std::uint32_t
		{
			kNone = 0,
			kSayingHello = 1 << 0,
			kEndResultRun = 1 << 1,
			kEvpBufferedUntil3DLoaded = 1 << 2,
			kInDialogueScenePlayer = 1 << 3,
			kHasHoldPackageScene = 1 << 4,
			kChargenSkeleton = 1 << 5,
			kHasInfoStartSceneRun = 1 << 6,
			kFadingVoice = 1 << 7,
			kDisableNonCombatHealRateBonus = 1 << 8,
			kOnlyRunScenePackage = 1 << 9,
			kDisableQueued = 1 << 10,
			kOnWaterNavMesh = 1 << 11,
			kSkipInventoryReset = 1 << 12,
			kNoCommandSceneState = 1 << 13,
			kEvalSceneStopCombat = 1 << 14,

			kSaveMask = 0x0FFFFFFDF
		};

		// add
		virtual void PlayPickUpSound(TESBoundObject* a_boundObj, bool a_pickUp, bool a_use);																													   // 0C6
		virtual REX::Float32 GetHeading() const;																																								   // 0C7 - { return data.angle.z; }
		virtual void SetAvoidanceDisabled(bool a_tf);																																							   // 0C8 - { return; }
		virtual void DrawWeaponMagicHands(bool a_draw);																																							   // 0C9
		virtual void SetPosition(const NiPoint3& a_position, bool a_updateCharController);																														   // 0CA
		virtual void KillDying();																																												   // 0CB
		virtual void Resurrect(bool a_resetInventory, bool a_attach3D);																																			   // 0CC
		virtual bool PutActorInChairBedQuick(TESObjectREFR* a_furniture, std::uint32_t a_index);																												   // 0CD
		virtual bool PutActorOnMountQuick();																																									   // 0CE
		virtual void Update(REX::Float32 a_delta);																																								   // 0CF
		virtual void UpdateNoAI(REX::Float32);																																									   // 0D0
		virtual void UpdateMotionDrivenState();																																									   // 0D1
		virtual void UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_charController);																										   // 0D2
		virtual void PotentiallyFixRagdollState();																																								   // 0D3
		virtual void UpdateNonRenderSafe(REX::Float32);																																							   // 0D4
		virtual bool ShouldHandleEquipNow() const;																																								   // 0D5
		virtual void SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_value);																											   // 0D6
		virtual std::uint32_t ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);																									   // 0D7
		virtual void RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);																											   // 0D8
		virtual std::uint32_t GetCrimeGoldValue(const TESFaction* a_faction) const;																																   // 0D9
		virtual void GoToPrison(TESFaction* a_faction, bool a_removeItems, bool a_realJail);																													   // 0DA - { return; }
		virtual void ServePrisonTime();																																											   // 0DB - { return; }
		virtual void PayFine(TESFaction* a_faction, bool a_movetoMarker, bool a_removeStolenItems);																												   // 0DC - { return; }
		virtual REX::Float32 GetCurrentEyeLevel() const;																																						   // 0DD
		virtual void SetInDialogueWithPlayer(bool a_set);																																						   // 0DE
		virtual bool GetCannibal();																																												   // 0DF - { return false; }
		virtual void SetCannibal(bool);																																											   // 0E0 - { return; }
		virtual bool GetVampireFeed();																																											   // 0E1 - { return false; }
		virtual void SetVampireFeed(bool);																																										   // 0E2 - { return; }
		virtual void InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);																													   // 0E3
		virtual void InitiateCannibalPackage(Actor* a_target);																																					   // 0E4
		virtual REX::Float32 GetEyeHeading() const;																																								   // 0E5
		virtual void GetEyeAngles(REX::Float32& a_eyeHeading, REX::Float32& a_eyeLooking) const;																												   // 0E6
		virtual void GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset) const;																									   // 0E7
		virtual void SetRefraction(bool a_enable, REX::Float32 a_refractionPower);																																   // 0E8
		virtual REX::Float32 GetAcrobatics() const;																																								   // 0E9 - { return 1.0_f32; }
		virtual bool Get3DUpdateFlag(RESET_3D_FLAGS a_flags) const;																																				   // 0EA
		virtual ObjectRefHandle DropObject(const BGSObjectInstance& a_object, BSTSmallArray<std::uint32_t, 4>* a_stackData, std::int32_t a_number, const NiPoint3* a_point, const NiPoint3* a_rotate);			   // 0EB
		virtual void PickUpObject(TESObjectREFR* a_objREFR, std::int32_t a_count, bool a_playPickUpSounds);																										   // 0EC
		virtual void AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);																										   // 0ED
		virtual void DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);																										   // 0EE
		virtual bool ReloadWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex);																								   // 0EF
		virtual std::uint32_t UseAmmo(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex, std::uint32_t a_shotCount);																   // 0F0
		virtual bool CalculateCachedOwnerIsInCombatantFaction() const;																																			   // 0F1
		virtual CombatGroup* GetCombatGroup() const;																																							   // 0F2
		virtual void SetCombatGroup(CombatGroup* a_group);																																						   // 0F3
		virtual bool CheckValidTarget(TESObjectREFR& a_ref) const;																																				   // 0F4
		virtual bool InitiateDialogue(Actor* a_target, PackageLocation* a_packLoc, PackageLocation* a_packSecondLoc);																							   // 0F5
		virtual void EndDialogue();																																												   // 0F6
		virtual Actor* SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_talkingActivator);																													   // 0F7
		virtual void InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runonce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, REX::Float32 a_fleeFromDist, REX::Float32 a_fleeToDist); // 0F8
		virtual void InitiateGetUpPackage();																																									   // 0F9
		virtual void PutCreatedPackage(TESPackage* a_pack, bool a_tempPack, bool a_isACreatedPackage, bool a_allowFromFurniture);																				   // 0FA
		virtual void UpdateAlpha();																																												   // 0FB
		virtual void SetAlpha(REX::Float32 a_newAlpha);																																							   // 0FC
		virtual REX::Float32 GetAlpha();																																										   // 0FD
		virtual bool IsInCombat() const;																																										   // 0FE
		virtual void UpdateCombat();																																											   // 0FF
		virtual void StopCombat();																																												   // 100
		virtual bool GetUsesAttackPercents();																																									   // 101 - { return false; }
		virtual std::uint8_t GetPowerAttackPercent(POWER_ATTACK_TYPE);																																			   // 102 - { return 0; }
		virtual void WeaponSwingCallBack(BGSEquipIndex a_equipIndex);																																			   // 103
		virtual void SetActorStartingPosition();																																								   // 104
		virtual void SetLifeState(ACTOR_LIFE_STATE a_lifeState);																																				   // 105
		virtual bool HasBeenAttacked();																																											   // 106
		virtual void SetBeenAttacked(bool a_set);																																								   // 107
		virtual void UseSkill(ActorValueInfo*, REX::Float32, TESForm*);																																			   // 108 - { return; }
		virtual bool IsAtPoint(const NiPoint3& a_point, REX::Float32 a_radius, bool a_expandRadius, bool a_alwaysTestHeight);																					   // 109
		virtual bool IsInFaction(const TESFaction* a_faction) const;																																			   // 10A
		virtual bool HasPerkEntries(std::uint8_t a_entryPoint) const;																																			   // 10B
		virtual void ForEachPerkEntry(std::uint8_t a_entryPoint, PerkEntryVisitor& a_visitor) const;																											   // 10C
		virtual void ApplyPerksFromBase();																																										   // 10D
		virtual void StartPowerAttackCoolDown();																																								   // 10E - { return; }
		virtual bool IsPowerAttackCoolingDown() const;																																							   // 10F - { return false; }
		virtual void HandleHealthDamage(Actor* a_attacker, REX::Float32 a_damage);																																   // 110
		virtual bool QSpeakingDone() const;																																										   // 111
		virtual void SetSpeakingDone(bool a_done);																																								   // 112
		virtual NiPoint3 CalculateLOSLocation(ACTOR_LOS_LOCATION a_location) const;																																   // 113
		virtual void CreateMovementController();																																								   // 114
		virtual bool ShouldPivotToFaceCamera() const;																																							   // 115 - { return false; }
		virtual BGSKeyword* GetSpeakingAnimArchType();																																							   // 116 - { return speakingAnimArchType; }
		virtual void KillImpl(Actor* a_attacker, REX::Float32 a_damage, bool a_sendEvent, bool a_ragdollInstant);																								   // 117
		virtual void DoReparentWeapon(const TESObjectWEAP* a_weapon, BGSEquipIndex a_equipIndex, bool a_weaponDrawn);																							   // 118
		virtual bool DrinkPotion(AlchemyItem* a_potion, std::uint32_t a_stackID);																																   // 119
		virtual bool CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason);																									   // 11A
		virtual void CheckTempModifiers();																																										   // 11B - { return; }
		virtual void SetLastRiddenMount(ActorHandle a_mount);																																					   // 11C - { return; }
		virtual ActorHandle QLastRiddenMount() const;																																							   // 11D
		virtual bool CalculateCachedOwnerIsUndead() const;																																						   // 11E
		virtual bool CalculateCachedOwnerIsNPC() const;																																							   // 11F
		virtual bool SetSneaking(bool a_sneaking);																																								   // 120
		virtual void ResetHavokPhysics();																																										   // 121
		virtual bool ShouldDoCharacterUpdate() const;																																							   // 122 - { return true; }
		virtual bool GetAnimationCanBeInterpolated() const;																																						   // 123
		virtual const BSFixedString& GetResponseString() const;																																					   // 124
		virtual void ModifyMovementData(REX::Float32 a_delta, NiPoint3& a_moveDelta, NiPoint3& a_angleDelta);																									   // 125
		virtual void UpdateCombatControllerSettings();																																							   // 126
		virtual void UpdateFadeSettings(bhkCharacterController* a_charController);																																   // 127
		virtual bool ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, REX::Float32 a_delta, ActorMotionFeedbackOutput& a_retData);													   // 128
		virtual bool UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_data);																												   // 129
		virtual void UpdateActor3DPosition();																																									   // 12A
		virtual void PrecacheData();																																											   // 12B
		virtual void WornArmorChanged(const BGSObjectInstance& a_object);																																		   // 12C
		virtual void ProcessTracking(REX::Float32 a_delta, NiAVObject* a_ob3D);																																	   // 12D
		virtual void CreateActorMover();																																										   // 12E
		virtual void DestroyActorMover();																																										   // 12F
		virtual bool ShouldRespondToActorCollision(const MovementMessageActorCollision&, const ActorHandlePtr& a_otherActor) const;																				   // 130
		virtual REX::Float32 CheckClampDamageModifier(ActorValueInfo& a_info, REX::Float32 a_delta);																											   // 131
		virtual void ValidateNewPath(const MovementMessageNewPath& a_newPathMessage);																															   // 132 - { return; }

		void AddPerk(BGSPerk* a_perk, std::uint8_t a_rank = 0);
		[[nodiscard]] bool CanUseIdle(TESIdleForm* a_idle) const;
		void ClearAttackStates();
		void EndInterruptPackage(bool a_notRunOnceDialogue);
		void ExitCover();
		void ForceDetect(Actor* a_target, bool a_forceLOS, REX::Float32 a_time);
		[[nodiscard]] TESNPC* GetActorBase() const;
		[[nodiscard]] ActorHandle GetActorHandle() const;
		void GetAimVector(NiPoint3& a_aimVector) const;
		[[nodiscard]] BGSBodyPartData* GetBodyPartData() const;
		[[nodiscard]] NiAVObject* GetClosestBone(NiPoint3 a_impactLocation, NiPoint3 a_movementDirection) const;
		[[nodiscard]] CFilter GetCollisionFilter() const;
		[[nodiscard]] TESCombatStyle* GetCombatStyle() const;
		[[nodiscard]] TESFaction* GetCrimeTrackingFaction() const;
		[[nodiscard]] TESAmmo* GetCurrentAmmo(BGSEquipIndex a_equipIndex) const;
		[[nodiscard]] std::uint32_t GetCurrentCollisionGroup() const;
		[[nodiscard]] bool GetCurrentFireLocation(BGSEquipIndex a_index, NiPoint3& a_fireLocation) const;
		[[nodiscard]] REX::Float32 GetDesiredSpeed() const;
		[[nodiscard]] BGSObjectInstance* GetEquippedItem(BGSObjectInstance* a_result, BGSEquipIndex a_equipIndex) const;
		[[nodiscard]] bool GetGhost() const;
		[[nodiscard]] REX::Float32 GetHealthPercentage();
		[[nodiscard]] bool GetHostileToActor(Actor* a_actor) const;
		[[nodiscard]] std::uint8_t GetMobilityCrippled() const;
		[[nodiscard]] ActorHandle GetMountHandle() const;
		[[nodiscard]] std::int16_t GetLevel() const;
		[[nodiscard]] bool GetOfferBarter();
		[[nodiscard]] std::uint8_t GetPerkRank(BGSPerk* a_perk) const;
		[[nodiscard]] SEX GetSex() const;
		[[nodiscard]] TESNPC* GetTemplateBase() const;
		void HandleDefaultAnimationSwitch();
		void HandleItemEquip(bool a_cullBone);
		bool HasObjects(TESBoundObject* a_obj, PACKAGE_OBJECT_TYPE a_formID, std::int32_t a_number, std::uint32_t a_id, PACKAGE_OBJECT_TYPE& a_matchID);
		void InitiateDoNothingPackage();
		[[nodiscard]] bool IsCrippled() const;
		[[nodiscard]] bool IsFollowing() const;
		[[nodiscard]] bool IsJumping() const;
		[[nodiscard]] bool IsPathValid() const;
		[[nodiscard]] bool IsPathing() const;
		[[nodiscard]] bool IsPathingComplete() const;
		[[nodiscard]] bool IsQuadruped() const;
		[[nodiscard]] bool IsSneaking() const;
		[[nodiscard]] bool IsVisible() const;
		void Jump(REX::Float32 a_height);
		bhkCharacterController* Move(REX::Float32 a_deltaTime, NiPoint3 a_deltaPos, bool a_defer);
		bool PerformAction(BGSAction* a_action, TESObjectREFR* a_target);
		void RemovePerk(BGSPerk* a_perk);
		void Reset3D(bool a_reloadAll, RESET_3D_FLAGS a_additionalFlags, bool a_queueReset, RESET_3D_FLAGS a_excludeFlags);
		void RewardExperience(REX::Float32 a_amount, bool a_direct, TESObjectREFR* a_actionTarget, TESObjectREFR* a_killWeapon);
		void SPECIALModifiedCallback(const ActorValueInfo* a_info, REX::Float32 a_originalValue, REX::Float32 a_delta);
		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo) const;
		void SetCurrentAmmoCount(BGSEquipIndex a_equipIndex, std::uint32_t a_count);
		void SetGunState(GUN_STATE a_gunState, bool a_set);
		void SetHeading(REX::Float32 a_angle);
		void StopInteractingQuick(bool a_instance, bool a_moveActor, bool a_update3D);
		void TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_owner, std::int32_t a_crime);
		void UnequipObject(TESBoundObject* a_object, ObjectEquipParams a_params);
		void UpdateSprinting();
		void UpdateVoiceTimer(bool a_force);

		// members
		REX::EnumSet<NiFlags, std::uint32_t> niFlags;				 // 2D0
		REX::Float32 updateTargetTimer;								 // 2D4
		NiPoint3 editorLocCoord;									 // 2D8
		NiPoint3 editorLocRot;										 // 2E4
		TESForm* editorLocForm;										 // 2F0
		BGSLocation* editorLocation;								 // 2F8
		AIProcess* currentProcess;									 // 300
		ActorMover* actorMover;										 // 308
		BGSKeyword* speakingAnimArchType;							 // 310
		BSTSmartPointer<MovementControllerNPC> movementController;	 // 318
		TESPackage* initialPackage;									 // 320
		CombatController* combatController;							 // 328
		TESFaction* vendorFaction;									 // 330
		ActorValueStorage avStorage;								 // 338
		BGSDialogueBranch* exclusiveBranch;							 // 370
		REX::Enum<ACTOR_CRITICAL_STAGE, std::int32_t> criticalStage; // 378
		ObjectRefHandle dialogueItemTarget;							 // 37C
		ActorHandle currentCombatTarget;							 // 380
		ActorHandle myKiller;										 // 384
		REX::Float32 checkMyDeadBodyTimer;							 // 388
		REX::Float32 voiceTimer;									 // 38C
		REX::Float32 voiceLengthTotal;								 // 390
		REX::Float32 underWaterTimer;								 // 394
		std::int32_t thiefCrimeStamp;								 // 398
		std::int32_t actionValue;									 // 39C
		REX::Float32 timerOnAction;									 // 3A0
		AITimeStamp calculateVendorFactionTimer;					 // 3A4
		std::uint32_t intimidateBribeDayStamp;						 // 3A8
		REX::Float32 equippedWeight;								 // 3AC
		BSTSmallArray<SpellItem*> addedSpells;						 // 3B0
		std::array<ActorMagicCaster*, 4> magicCasters;				 // 3C8
		std::array<MagicItem*, 4> selectedSpell;					 // 3E8
		CastPowerItem* castPowerItems;								 // 408
		TESForm* selectedPower;										 // 410
		TESRace* race;												 // 418
		Perks* perks;												 // 420
		BSTSmartPointer<BipedAnim> biped;							 // 428
		mutable BSNonReentrantSpinLock addingToOrRemovingFromScene;	 // 430
		mutable BSReadWriteLock perkArrayLock;						 // 434
		REX::EnumSet<BOOL_FLAGS, std::uint32_t> boolFlags;			 // 43C
		std::uint32_t moreFlags;									 // 440
		Modifiers healthModifiers;									 // 444
		Modifiers actionPointsModifiers;							 // 450
		Modifiers staminaModifiers;									 // 45C
		Modifiers radsModifiers;									 // 468
		REX::Float32 lastUpdate;									 // 474
		std::uint32_t lastSeenTime;									 // 478
		REX::Float32 armorRating;									 // 47C
		REX::Float32 armorBaseFactorSum;							 // 480
		std::uint32_t visFlags		  : 4;							 // 484:00
		std::int8_t raceSwitchPending : 1;							 // 488:0
		std::int8_t soundCallBackSet;								 // 489
		bool trespassing;											 // 48A
	};
	static_assert(sizeof(Actor) == 0x490);
}

#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/A/Actor.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/C/CrimeGoldStruct.hpp"
#include "RE/F/FriendshipFactionsStruct.hpp"
#include "RE/I/IMovementPlayerControlsFilter.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTMap.hpp"
#include "RE/P/PLAYER_TARGET_LOC.hpp"
#include "RE/P/PlayerAutoAimActorEvent.hpp"
#include "RE/P/PlayerCommandTypeEvent.hpp"
#include "RE/P/PlayerCoverData.hpp"
#include "RE/S/SayOnceTimeStampStruct.hpp"
#include "RE/S/StolenItemValueStruct.hpp"
#include "RE/S/SubgraphHandle.hpp"
#include "RE/X/XPChangeData.hpp"

namespace RE::BGSCharacterTint
{
	class Entries;
}

namespace RE::PerkValueEvents
{
	class PerkEntryUpdatedEvent;
}

namespace RE
{
	enum class DEFAULT_OBJECT : std::int32_t;
	enum class DifficultyLevel : std::int32_t;
	enum class PLAYER_ACTION : std::int32_t;
	enum class SCENE_ACTION_PLAYER_RESPONSE_TYPE : std::int32_t;

	class BGSActorCellEvent;
	class BGSActorDeathEvent;
	class BGSInstancedQuestObjective;
	class BipedAnim;
	class BSLight;
	class BSPathingSolution;
	class CombatGroup;
	class Crime;
	class EquippedItem;
	class ImageSpaceModifierInstanceDOF;
	class ImageSpaceModifierInstanceForm;
	class ItemChange;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class OtherEventEnabledEvent;
	class PickRefUpdateEvent;
	class PlayerActionObject;
	class PositionPlayerEvent;
	class QuestTargetArray;
	class TeleportPath;
	class TESHitEvent;
	class TESQuestStageItem;
	class UserEventEnabledEvent;

	class __declspec(novtable) PlayerCharacter
		: public Actor,												   // 000
		  public BSTEventSource<BGSActorCellEvent>,					   // 4C8
		  public BSTEventSource<BGSActorDeathEvent>,				   // 520
		  public BSTEventSource<PositionPlayerEvent>,				   // 578
		  public BSTEventSource<PickRefUpdateEvent>,				   // 5D0
		  public BSTEventSink<MenuOpenCloseEvent>,					   // 490
		  public BSTEventSink<MenuModeChangeEvent>,					   // 498
		  public BSTEventSink<UserEventEnabledEvent>,				   // 4A0
		  public BSTEventSink<OtherEventEnabledEvent>,				   // 4A8
		  public BSTEventSink<TESHitEvent>,							   // 4B0
		  public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>, // 4B8
		  public IMovementPlayerControlsFilter						   // 4C0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PlayerCharacter };
		inline static constexpr auto VTABLE{ VTABLE::PlayerCharacter };
		inline static constexpr auto FORM_TYPE{ FormType::kActor };

		enum class CHAR_GEN_DISABLE_FLAGS : std::uint32_t
		{
			kNone = 0,
			kDisableSave = 1 << 0,
			kDisableWait = 1 << 1,
			kShowControlsDisabledMessage = 1 << 2
		};

		enum class GrabbingType : std::int32_t
		{
			kNone = 0,
			kNormal = 1,
			kTelekinesis = 2
		};

		enum class PROGRESS_EVENT : std::int32_t
		{
			kLevelUp = 0,
			kDeath = 1,
			kChargen = 2
		};

		class PlayerActionObject
		{
		public:
			// members
			REX::Float32 timer;							 // 00
			ObjectRefHandle refObj;						 // 04
			REX::Enum<PLAYER_ACTION, std::int32_t> next; // 08
		};
		static_assert(sizeof(PlayerActionObject) == 0x0C);

		class ScopedInventoryChangeMessageContext
		{
		public:
			// members
			bool suppressMessages; // 00
			bool suppressAudio;	   // 01
		};
		static_assert(sizeof(ScopedInventoryChangeMessageContext) == 0x02);

		// add
		virtual void InitiateSpectator(Actor* a_actor);									// 133 - { return; }
		virtual std::uint32_t GetViolentCrimeGoldValue(const TESFaction* a_faction);	// 134
		virtual std::uint32_t GetNonViolentCrimeGoldValue(const TESFaction* a_faction); // 135
		virtual void ClearAllCrimeGold(TESFaction* a_faction);							// 136

		[[nodiscard]] static PlayerCharacter* GetSingleton();
		[[nodiscard]] static ActorHandle GetPlayerHandle();

		void ClearPrison();
		void EnableRadio(bool a_enable);
		[[nodiscard]] DifficultyLevel GetDifficultyLevel() const;
		[[nodiscard]] bool HasLOSToTarget(Actor* a_targetRef, bool& a_pickPerformed);
		[[nodiscard]] bool IsGodMode() const;
		[[nodiscard]] bool IsHolotapePlaying(BGSNote* a_holotape) const;
		[[nodiscard]] bool IsImmortal() const;
		[[nodiscard]] bool IsLockedOutOfTerminal(ObjectRefHandle a_refHandle);
		[[nodiscard]] bool IsPipboyLightOn() const noexcept;
		void LockOutOfTerminal(ObjectRefHandle a_refHandle);
		void PauseHolotape(BGSNote* a_holotape);
		void PlayHolotape(BGSNote* a_holotape);
		void QueueFastTravel(ObjectRefHandle a_marker, bool a_allowAutoSave);
		void RemoveLastUsedPowerArmor();
		void SelectPerk(TESFormID a_formID, std::int8_t a_rank = 0);
		void SetAIControlledPackage(bool a_enable);
		void SetEscaping(bool a_set, bool a_escaped);
		void SetLastDialogueInput(std::uint32_t a_dialogueOption);
		void SetPerkCount(std::uint8_t a_count);
		void SetTintingData(std::uint16_t a_uniqueID, REX::Float32 a_value, std::uint32_t a_color);
		void SetVATSCriticalCount(std::uint32_t a_critCount);
		void ShowPipboyLight(bool a_show, bool a_skipEffects);
		void StopHolotape(BGSNote* a_holotape);

		// members
		mutable BSSpinLock actorToDisplayOnHUDLock;										// 628
		mutable BSSpinLock questTargetLock;												// 630
		BSTHashMap<const TESFaction*, CrimeGoldStruct> crimeGoldMap;					// 638
		BSTHashMap<const TESFaction*, StolenItemValueStruct> stolenItemValueMap;		// 668
		PlayerCoverData coverData;														// 698
		ObjectRefHandle commandWaitMarker;												// 6C4
		BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap; // 6C8
		NiPoint3A lastKnownGoodPosition;												// 700
		NiPoint3A lastKnownGoodNavmeshPosition;											// 710
		NiPoint3 bulletAutoAim;															// 720
		NiPoint3 cachedVelocity;														// 72C
		BSTArray<ObjectRefHandle> currentMapMarkers;									// 738
		BSTArray<BSTPair<NiPoint3, AITimeStamp>> velocityArray;							// 750
		BSTArray<ProjectileHandle> runesCast;											// 768
		BSTArray<TESImageSpaceModifier*> animationImageSpaceModifiers;					// 78-
		BSTArray<ImageSpaceModifierInstanceForm*> animationImageSpaceInstances;			// 798
		BSTArray<BSTPair<NiPointer<NiLight>, bool>> playerLights;						// 7B0
		BSSimpleList<TESQuestStageItem*> questLog;										// 7C8
		BSTArray<BGSInstancedQuestObjective> objectives;								// 7D9
		BSTHashMap<TESQuest*, QuestTargetArray*> questTargets;							// 7F0
		BSTHashMap<TESFormID, SayOnceTimeStampStruct> currentSayOnceInfosMap;			// 820
		BSTHashMap<TESFormID, SayOnceTimeStampStruct> currentSpeechRepeatMap;			// 850
		BSSimpleList<ObjectRefHandle> droppedRefList;									// 880
		NiTMap<TESFormID, std::uint8_t> randomDoorSpaceMap;								// 890
		TESWorldSpace* cachedWorldspace;												// 8B0
		NiPoint3 exteriorPosition;														// 8B8
		BSTSmallArray<SubgraphHandle, 2> pipboyAnimSubGraph;							// 8C8
		PLAYER_TARGET_LOC queuedTargetLoc;												// 8E8
		PLAYER_TARGET_LOC queuedFlightLoc;												// 948
		NiPoint3A flightGridCenter;														// 9B0
		BSPathingSolution* flightMountPathingSolution;									// 9C0
		TESObjectCELL* flightMountPreloadCell;											// 9C8
		BSSoundHandle magicFailureSound;												// 9D0
		BSTArray<TESFormID> rumorTopicInfoList;											// 9D8
		TESFormID testChallengeInfoID;													// 9F0
		DialoguePackage* closestConversation;											// 9F8
		DialoguePackage* aiConversationRunning;											// A00
		std::int32_t numberofStealWarnings;												// A08
		REX::Float32 stealWarningTimer;													// A0C
		std::int32_t numberofPickpocketWarnings;										// A10
		REX::Float32 pickPocketWarningTimer;											// A14
		AITimeStamp warnToLeaveTimeStamp;												// A18
		AITimeStamp usingTeleportDoorTimeStamp;											// A1C
		NiPointer<ImageSpaceModifierInstanceDOF> ironSightsDOFInstance;					// A20
		TESFaction* currentPrisonFaction;												// A28
		std::uint32_t jailSentence;														// A30
		NiPointer<NiAVObject> autoAimDebugSphere;										// A38
		BGSNote* currHolotape;															// A40
		BSSoundHandle soundHand;														// A48
		std::int32_t vampireFeedDetection;												// A50
		std::uint32_t mapMarkerIterator;												// A54
		ObjectRefHandle forceActivateRef;												// A58
		ObjectRefHandle loopingActivateRef;												// A5C
		TESFormID dialogueCameraLastSceneID;											// A60
		std::array<PlayerActionObject, 15> playerActionObjects;							// A64
		REX::Enum<PLAYER_ACTION, std::int32_t> mostRecentAction;						// B18
		ActorHandle actorDoingPlayerCommand;											// B1C
		BSTValueEventSource<PlayerCommandTypeEvent> playerCurrentCommandType;			// B20
		BSTArray<void*> grabSprings;													// B38 - BSTArray<hkRefPtr<hknpBSMouseSpringAction>>
		NiPoint3 grabUserRotation;														// B50
		ObjectRefHandle grabbedObject;													// B5C
		REX::Float32 grabObjectWeight;													// B60
		REX::Float32 grabDistance;														// B64
		std::uint32_t secondsToSleepPerUpdate;											// B68
		std::uint32_t sleepSeconds;														// B6C
		BSTSmartPointer<BipedAnim> firstPersonBipedAnim;								// B70
		NiPointer<NiNode> firstPerson3D;												// B78
		NiAVObject* firstPersonTorso;													// B80
		NiAVObject* firstPersonEye;														// B88
		REX::Float32 eyeHeight;															// B90
		REX::Float32 greetTimer;														// B94
		REX::Float32 encumberedTimer;													// B98
		REX::Float32 powerAttackTimer;													// B9C
		REX::Float32 autoReloadTimer;													// BA0
		REX::Float32 pivotToFaceCamera;													// BA4
		std::int32_t hoursToSleep;														// BA8
		std::int32_t amountStolenSold;													// BAC
		std::uint32_t valueStolen;														// BB0
		ActorHandle lastRiddenMount;													// BB4
		ActorHandle lightTarget;														// BB8
		REX::Float32 sortActorDistanceTimer;											// BBC
		REX::Float32 sitHeadingDelta;													// BC0
		ObjectRefHandle playerMapMarker;												// BC4
		TeleportPath* playerMarkerPath;													// BC8
		std::uint32_t skillTrainingsThisLevel;											// BD0
		TESClass* defaultClass;															// BD8
		std::array<std::uint32_t, 7> crimeCounts;										// BE0
		AlchemyItem* pendingPoison;														// C00
		std::time_t lastPlayingTimeUpdate;												// C08
		std::time_t totalPlayingTime;													// C10
		std::uint32_t characterSeed;													// C18
		TESForm* lastKnownGoodLocation;													// C20
		NiPointer<BSLight> firstPersonLight;											// C28
		NiPointer<BSLight> thirdPersonLight;											// C30
		NiPointer<BSLight> pipboyLight;													// C38
		NiPointer<NiLight> niPipboyLight;												// C40
		REX::Float32 dropAngleMod;														// C48
		REX::Float32 lastDropAngleMod;													// C4C
		BSTValueEventSource<PlayerAutoAimActorEvent> autoAimActor;						// C50
		ObjectRefHandle homingTarget;													// C68
		REX::Float32 homingTargetTimer;													// C6C
		NiPointer<NiAVObject> targeted3D;												// C70
		CombatGroup* combatGroup;														// C78
		BSTArray<ActorHandle> actorsToDisplayOnTheHUD;									// C80
		BSTArray<EquippedItem> lastOneHandItems;										// C98
		std::uint32_t teammateCount;													// CB0
		REX::Float32 combatTimer;														// CB4
		REX::Float32 yieldTimer;														// CB8
		REX::Float32 chaseTimer;														// CBC
		REX::Float32 drawSheatheSafetyTimer;											// CC0
		std::uint32_t activeCombatantCount;												// CC4
		BGSLocation* currentLocation;													// CC8
		AITimeStamp cachedVelocityTimeStamp;											// CD0
		REX::Float32 telekinesisDistance;												// CD4
		REX::Float32 commandTimer;														// CD8
		REX::Float32 dialogueCameraChangeRate;											// CDC
		REX::Float32 fireWeaponEventTimer;												// CE0
		REX::Enum<DEFAULT_OBJECT, std::int32_t> animationObjectAction;					// CE4
		REX::Enum<GrabbingType, std::int32_t> grabType;									// CE8
		ActorHandle assumedIdentity;													// CEC
		std::uint8_t murder;															// CF0
		std::uint8_t perkCount;															// CF1
		std::uint8_t byCharGenFlag;														// CF2
		Crime* resistArrestCrime;														// CF8
		BGSCharacterTint::Entries* tintingData;											// D00
		BGSTextureSet* complexion;														// D08
		TESRace* charGenRace;															// D10
		EffectSetting* currentAlchemyEffect;											// D18
		ItemChange* currentTemperingInventoryItem;										// D20
		TESObjectREFR* commandTarget;													// D28
		TESObjectREFR* walkThroughDoor;													// D30
		REX::Enum<COMMAND_TYPE, std::int32_t> currentCommand;							// D38
		REX::Enum<SCENE_ACTION_PLAYER_RESPONSE_TYPE, std::int32_t> playerDialogueInput; // D3C
		ActorValueInfo* stimpakTarget;													// D40
		REX::Float32 vatsCriticalCharge;												// D48
		std::uint32_t vatsCriticalCount;												// D4C
		std::uint32_t maxVATSCriticalCount;												// D50
		REX::Float32 timeBlendingOutFirstPersonOffset;									// D54
		ActorHandle lastMagnetismActor;													// D58
		NiPoint3 magnetismActorPos;														// D5C
		ObjectRefHandle workstationBeingLeft;											// D68
		ActorHandle actorLeavingWorkstation;											// D6C
		BGSScene* allowDialogueCameraScene;												// D70
		ActorHandle helloActor;															// D78
		TESObjectREFR* weaponAmmoRef;													// D80
		std::int32_t equippingAmmoCount;												// D88
		REX::Float32 dialogueCameraResumeTimer;											// D8C
		ObjectRefHandle lastUsedPowerArmor;												// D90
		TeleportPath* lastUsedPowerArmorMarkerPath;										// D98
		TESObjectWEAP* lastUsedThrownWeapon;											// DA0
		BSSoundHandle powerArmorInteriorSoundHandle;									// DA8
		BSTArray<BSTPair<ObjectRefHandle, REX::Float32>> lockedTerminals;				// DB0
		BSTArray<BSTPair<std::int32_t, std::int32_t>> boneMapping1stTo3rd;				// DC8
		BSTOptional<XPChangeData> syncedXPChange;										// DE0
		std::int32_t queuedSwitch : 1;													// DF4:00
		std::uint32_t charGenHUDMode;													// DF8
		bool insideMemoryHUDMode			  : 1;										// DFC:0
		bool xpSyncedWithHUDNotification	  : 1;										// DFC:1
		bool travelUseDoor					  : 1;										// DFC:2
		bool transporting					  : 1;										// DFC:3
		bool overAutoAimTarget				  : 1;										// DFC:4
		bool showQuestItemsInInventory		  : 1;										// DFC:5
		bool hostileDetection				  : 1;										// DFC:6
		bool escaping						  : 1;										// DFC:7
		bool forceQuestTargetRepath			  : 1;										// DFD:0
		bool speaking						  : 1;										// DFD:1
		bool isSleeping						  : 1;										// DFD:2
		bool actorInSneakRange				  : 1;										// DFD:3
		bool greetingPlayer					  : 1;										// DFD:4
		bool beenAttacked					  : 1;										// DFD:5
		bool allowEGMCacheClear				  : 1;										// DFD:6
		bool aiControlledToPos				  : 1;										// DFD:7
		bool aiControlledFromPos			  : 1;										// DFE:0
		bool aiControlledPackage			  : 1;										// DFE:1
		bool returnToLastKnownGoodPosition	  : 1;										// DFE:2
		bool beingChased					  : 1;										// DFE:3
		bool is3rdPersonModelShown			  : 1;										// DFE:4
		bool hideFirstPersonGeometry		  : 1;										// DFE:5
		bool insufficientChargeMessageShownL  : 1;										// DFE:6
		bool insufficientChargeMessageShownR  : 1;										// DFE:7
		bool target3DDistant				  : 1;										// DFF:0
		bool playerInCombat					  : 1;										// DFF:1
		bool attemptedYieldInCurrentCombat	  : 1;										// DFF:2
		bool currentAlchemyIsPoison			  : 1;										// DFF:3
		bool positioning					  : 1;										// DFF:4
		bool crimeReporting					  : 1;										// DFF:5
		bool healthTutorialShown			  : 1;										// DFF:6
		bool magickaTutorialShown			  : 1;										// DFF:7
		bool staminaTutorialShown			  : 1;										// E00:0
		bool goToJailQueued					  : 1;										// E00:1
		bool doorAutosaveQueued				  : 1;										// E00:2
		bool sprintToggled					  : 1;										// E00:3
		bool useHighSpeedLoading			  : 1;										// E00:4
		bool sceneActionActive				  : 1;										// E00:5
		bool sayingHello					  : 1;										// E00:6
		bool disabledRadio					  : 1;										// E00:7
		bool updateAutoAimActor				  : 1;										// E01:0
		bool autoReload						  : 1;										// E01:1
		bool usingScopeWithOverlay			  : 1;										// E01:2
		bool steadyingWeapon				  : 1;										// E01:3
		bool speechChallengeReward			  : 1;										// E01:4
		bool blendOutFirstPersonOffset		  : 1;										// E01:5
		bool dialogueCameraConsiderResume	  : 1;										// E01:6
		bool shouldFollowerSupressIdleChatter : 1;										// E01:7
		bool idleChatter					  : 1;										// E02:0
		bool switchingPerspectives			  : 1;										// E02:1
		bool onElevator						  : 1;										// E02:2
		bool sayCommandResponse				  : 1;										// E02:3
		bool inLooksMenu					  : 1;										// E02:4
		bool playingTimeFrozen				  : 1;										// E02:5
		bool everModded						  : 1;										// E02:6
	};
	static_assert(sizeof(PlayerCharacter) == 0xE10);
}

namespace RE
{
	bool IsPlayerInDialogue();
}

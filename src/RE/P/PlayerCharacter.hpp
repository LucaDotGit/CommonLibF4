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
#include "RE/N/NiPoint3.hpp"
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

	class __declspec(novtable) PlayerCharacter :
		public Actor,												 // 0x000
		public BSTEventSource<BGSActorCellEvent>,					 // 0x4C8
		public BSTEventSource<BGSActorDeathEvent>,					 // 0x520
		public BSTEventSource<PositionPlayerEvent>,					 // 0x578
		public BSTEventSource<PickRefUpdateEvent>,					 // 0x5D0
		public BSTEventSink<MenuOpenCloseEvent>,					 // 0x490
		public BSTEventSink<MenuModeChangeEvent>,					 // 0x498
		public BSTEventSink<UserEventEnabledEvent>,					 // 0x4A0
		public BSTEventSink<OtherEventEnabledEvent>,				 // 0x4A8
		public BSTEventSink<TESHitEvent>,							 // 0x4B0
		public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>, // 0x4B8
		public IMovementPlayerControlsFilter						 // 0x4C0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PlayerCharacter;
		inline static constexpr const auto& VTABLE = VTABLE::PlayerCharacter;
		inline static constexpr auto FORM_TYPE = FormType::Actor;

		enum class CHAR_GEN_DISABLE_FLAGS : std::uint32_t
		{
			None = 0,
			DisableSave = 1 << 0,
			DisableWait = 1 << 1,
			ShowControlsDisabledMessage = 1 << 2
		};

		enum class GrabbingType : std::int32_t
		{
			None = 0,
			Normal = 1,
			Telekinesis = 2
		};

		enum class PROGRESS_EVENT : std::int32_t
		{
			LevelUp = 0,
			Death = 1,
			Chargen = 2
		};

		class PlayerActionObject
		{
		public:
			// members
			REX::Float32 timer;							 // 0x00
			ObjectRefHandle refObj;						 // 0x04
			REX::Enum<PLAYER_ACTION, std::int32_t> next; // 0x08
		};

		static_assert(sizeof(PlayerActionObject) == 0x0C);

		class ScopedInventoryChangeMessageContext
		{
		public:
			// members
			bool suppressMessages; // 0x00
			bool suppressAudio;	   // 0x01
		};

		static_assert(sizeof(ScopedInventoryChangeMessageContext) == 0x02);

		~PlayerCharacter() override; // 0x00

		// add
		virtual void InitiateSpectator(Actor* a_actor);											// 0x133 - { return; }
		virtual auto GetViolentCrimeGoldValue(const TESFaction* a_faction) -> std::uint32_t;	// 0x134
		virtual auto GetNonViolentCrimeGoldValue(const TESFaction* a_faction) -> std::uint32_t; // 0x135
		virtual void ClearAllCrimeGold(TESFaction* a_faction);									// 0x136

		[[nodiscard]]
		static auto GetSingleton() noexcept -> PlayerCharacter*;
		[[nodiscard]]
		static auto GetPlayerHandle() -> ActorHandle;

		void ClearPrison();
		void EnableRadio(bool a_enable);
		[[nodiscard]]
		auto GetDifficultyLevel() const -> DifficultyLevel;
		auto HandlePositionPlayerRequest() -> bool;
		[[nodiscard]]
		auto HasLOSToTarget(Actor* a_targetRef, bool& a_pickPerformed) -> bool;
		[[nodiscard]]
		auto IsGodMode() const -> bool;
		[[nodiscard]]
		auto IsHolotapePlaying(BGSNote* a_holotape) const -> bool;
		[[nodiscard]]
		auto IsImmortal() const -> bool;
		[[nodiscard]]
		auto IsLockedOutOfTerminal(ObjectRefHandle a_refHandle) -> bool;
		[[nodiscard]]
		auto IsPipboyLightOn() const noexcept -> bool;
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
		mutable BSSpinLock actorToDisplayOnHUDLock;										// 0x628
		mutable BSSpinLock questTargetLock;												// 0x630
		BSTHashMap<const TESFaction*, CrimeGoldStruct> crimeGoldMap;					// 0x638
		BSTHashMap<const TESFaction*, StolenItemValueStruct> stolenItemValueMap;		// 0x668
		PlayerCoverData coverData;														// 0x698
		ObjectRefHandle commandWaitMarker;												// 0x6C4
		BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap; // 0x6C8
		NiPoint3A lastKnownGoodPosition;												// 0x700
		NiPoint3A lastKnownGoodNavmeshPosition;											// 0x710
		NiPoint3 bulletAutoAim;															// 0x720
		NiPoint3 cachedVelocity;														// 0x72C
		BSTArray<ObjectRefHandle> currentMapMarkers;									// 0x738
		BSTArray<BSTPair<NiPoint3, AITimeStamp>> velocityArray;							// 0x750
		BSTArray<ProjectileHandle> runesCast;											// 0x768
		BSTArray<TESImageSpaceModifier*> animationImageSpaceModifiers;					// 0x780
		BSTArray<ImageSpaceModifierInstanceForm*> animationImageSpaceInstances;			// 0x798
		BSTArray<BSTPair<NiPointer<NiLight>, bool>> playerLights;						// 0x7B0
		BSSimpleList<TESQuestStageItem*> questLog;										// 0x7C8
		BSTArray<BGSInstancedQuestObjective> objectives;								// 0x7D8
		BSTHashMap<TESQuest*, QuestTargetArray*> questTargets;							// 0x7F0
		BSTHashMap<TESFormID, SayOnceTimeStampStruct> currentSayOnceInfosMap;			// 0x820
		BSTHashMap<TESFormID, SayOnceTimeStampStruct> currentSpeechRepeatMap;			// 0x850
		BSSimpleList<ObjectRefHandle> droppedRefList;									// 0x880
		NiTMap<TESFormID, std::uint8_t> randomDoorSpaceMap;								// 0x890
		TESWorldSpace* cachedWorldspace;												// 0x8B0
		NiPoint3 exteriorPosition;														// 0x8B8
		BSTSmallArray<SubgraphHandle, 2> pipboyAnimSubGraph;							// 0x8C8
		PLAYER_TARGET_LOC queuedTargetLoc;												// 0x8E8
		PLAYER_TARGET_LOC queuedFlightLoc;												// 0x948
		NiPoint3A flightGridCenter;														// 0x9B0
		BSPathingSolution* flightMountPathingSolution;									// 0x9C0
		TESObjectCELL* flightMountPreloadCell;											// 0x9C8
		BSSoundHandle magicFailureSound;												// 0x9D0
		BSTArray<TESFormID> rumorTopicInfoList;											// 0x9D8
		TESFormID testChallengeInfoID;													// 0x9F0
		DialoguePackage* closestConversation;											// 0x9F8
		DialoguePackage* aiConversationRunning;											// 0xA00
		std::int32_t numberofStealWarnings;												// 0xA08
		REX::Float32 stealWarningTimer;													// 0xA0C
		std::int32_t numberofPickpocketWarnings;										// 0xA10
		REX::Float32 pickPocketWarningTimer;											// 0xA14
		AITimeStamp warnToLeaveTimeStamp;												// 0xA18
		AITimeStamp usingTeleportDoorTimeStamp;											// 0xA1C
		NiPointer<ImageSpaceModifierInstanceDOF> ironSightsDOFInstance;					// 0xA20
		TESFaction* currentPrisonFaction;												// 0xA28
		std::uint32_t jailSentence;														// 0xA30
		NiPointer<NiAVObject> autoAimDebugSphere;										// 0xA38
		BGSNote* currHolotape;															// 0xA40
		BSSoundHandle soundHand;														// 0xA48
		std::int32_t vampireFeedDetection;												// 0xA50
		std::uint32_t mapMarkerIterator;												// 0xA54
		ObjectRefHandle forceActivateRef;												// 0xA58
		ObjectRefHandle loopingActivateRef;												// 0xA5C
		TESFormID dialogueCameraLastSceneID;											// 0xA60
		std::array<PlayerActionObject, 15> playerActionObjects;							// 0xA64
		REX::Enum<PLAYER_ACTION, std::int32_t> mostRecentAction;						// 0xB18
		ActorHandle actorDoingPlayerCommand;											// 0xB1C
		BSTValueEventSource<PlayerCommandTypeEvent> playerCurrentCommandType;			// 0xB20
		BSTArray<void*> grabSprings;					 // 0xB38 - To-Do: `BSTArray<hkRefPtr<hknpBSMouseSpringAction>>`
		NiPoint3 grabUserRotation;						 // 0xB50
		ObjectRefHandle grabbedObject;					 // 0xB5C
		REX::Float32 grabObjectWeight;					 // 0xB60
		REX::Float32 grabDistance;						 // 0xB64
		std::uint32_t secondsToSleepPerUpdate;			 // 0xB68
		std::uint32_t sleepSeconds;						 // 0xB6C
		BSTSmartPointer<BipedAnim> firstPersonBipedAnim; // 0xB70
		NiPointer<NiNode> firstPerson3D;				 // 0xB78
		NiAVObject* firstPersonTorso;					 // 0xB80
		NiAVObject* firstPersonEye;						 // 0xB88
		REX::Float32 eyeHeight;							 // 0xB90
		REX::Float32 greetTimer;						 // 0xB94
		REX::Float32 encumberedTimer;					 // 0xB98
		REX::Float32 powerAttackTimer;					 // 0xB9C
		REX::Float32 autoReloadTimer;					 // 0xBA0
		REX::Float32 pivotToFaceCamera;					 // 0xBA4
		std::int32_t hoursToSleep;						 // 0xBA8
		std::int32_t amountStolenSold;					 // 0xBAC
		std::uint32_t valueStolen;						 // 0xBB0
		ActorHandle lastRiddenMount;					 // 0xBB4
		ActorHandle lightTarget;						 // 0xBB8
		REX::Float32 sortActorDistanceTimer;			 // 0xBBC
		REX::Float32 sitHeadingDelta;					 // 0xBC0
		ObjectRefHandle playerMapMarker;				 // 0xBC4
		TeleportPath* playerMarkerPath;					 // 0xBC8
		std::uint32_t skillTrainingsThisLevel;			 // 0xBD0
		TESClass* defaultClass;							 // 0xBD8
		std::array<std::uint32_t, 7> crimeCounts;		 // 0xBE0
		AlchemyItem* pendingPoison;						 // 0xC00
		std::time_t lastPlayingTimeUpdate;				 // 0xC08
		std::time_t totalPlayingTime;					 // 0xC10
		std::uint32_t characterSeed;					 // 0xC18
		TESForm* lastKnownGoodLocation;					 // 0xC20
		NiPointer<BSLight> firstPersonLight;			 // 0xC28
		NiPointer<BSLight> thirdPersonLight;			 // 0xC30
		NiPointer<BSLight> pipboyLight;					 // 0xC38
		NiPointer<NiLight> niPipboyLight;				 // 0xC40
		REX::Float32 dropAngleMod;						 // 0xC48
		REX::Float32 lastDropAngleMod;					 // 0xC4C
		BSTValueEventSource<PlayerAutoAimActorEvent> autoAimActor;						// 0xC50
		ObjectRefHandle homingTarget;													// 0xC68
		REX::Float32 homingTargetTimer;													// 0xC6C
		NiPointer<NiAVObject> targeted3D;												// 0xC70
		CombatGroup* combatGroup;														// 0xC78
		BSTArray<ActorHandle> actorsToDisplayOnTheHUD;									// 0xC80
		BSTArray<EquippedItem> lastOneHandItems;										// 0xC98
		std::uint32_t teammateCount;													// 0xCB0
		REX::Float32 combatTimer;														// 0xCB4
		REX::Float32 yieldTimer;														// 0xCB8
		REX::Float32 chaseTimer;														// 0xCBC
		REX::Float32 drawSheatheSafetyTimer;											// 0xCC0
		std::uint32_t activeCombatantCount;												// 0xCC4
		BGSLocation* currentLocation;													// 0xCC8
		AITimeStamp cachedVelocityTimeStamp;											// 0xCD0
		REX::Float32 telekinesisDistance;												// 0xCD4
		REX::Float32 commandTimer;														// 0xCD8
		REX::Float32 dialogueCameraChangeRate;											// 0xCDC
		REX::Float32 fireWeaponEventTimer;												// 0xCE0
		REX::Enum<DEFAULT_OBJECT, std::int32_t> animationObjectAction;					// 0xCE4
		REX::Enum<GrabbingType, std::int32_t> grabType;									// 0xCE8
		ActorHandle assumedIdentity;													// 0xCEC
		std::uint8_t murder;															// 0xCF0
		std::uint8_t perkCount;															// 0xCF1
		std::uint8_t byCharGenFlag;														// 0xCF2
		Crime* resistArrestCrime;														// 0xCF8
		BGSCharacterTint::Entries* tintingData;											// 0xD00
		BGSTextureSet* complexion;														// 0xD08
		TESRace* charGenRace;															// 0xD10
		EffectSetting* currentAlchemyEffect;											// 0xD18
		ItemChange* currentTemperingInventoryItem;										// 0xD20
		TESObjectREFR* commandTarget;													// 0xD28
		TESObjectREFR* walkThroughDoor;													// 0xD30
		REX::Enum<COMMAND_TYPE, std::int32_t> currentCommand;							// 0xD38
		REX::Enum<SCENE_ACTION_PLAYER_RESPONSE_TYPE, std::int32_t> playerDialogueInput; // 0xD3C
		ActorValueInfo* stimpakTarget;													// 0xD40
		REX::Float32 vatsCriticalCharge;												// 0xD48
		std::uint32_t vatsCriticalCount;												// 0xD4C
		std::uint32_t maxVATSCriticalCount;												// 0xD50
		REX::Float32 timeBlendingOutFirstPersonOffset;									// 0xD54
		ActorHandle lastMagnetismActor;													// 0xD58
		NiPoint3 magnetismActorPos;														// 0xD5C
		ObjectRefHandle workstationBeingLeft;											// 0xD68
		ActorHandle actorLeavingWorkstation;											// 0xD6C
		BGSScene* allowDialogueCameraScene;												// 0xD70
		ActorHandle helloActor;															// 0xD78
		TESObjectREFR* weaponAmmoRef;													// 0xD80
		std::int32_t equippingAmmoCount;												// 0xD88
		REX::Float32 dialogueCameraResumeTimer;											// 0xD8C
		ObjectRefHandle lastUsedPowerArmor;												// 0xD90
		TeleportPath* lastUsedPowerArmorMarkerPath;										// 0xD98
		TESObjectWEAP* lastUsedThrownWeapon;											// 0xDA0
		BSSoundHandle powerArmorInteriorSoundHandle;									// 0xDA8
		BSTArray<BSTPair<ObjectRefHandle, REX::Float32>> lockedTerminals;				// 0xDB0
		BSTArray<BSTPair<std::int32_t, std::int32_t>> boneMapping1stTo3rd;				// 0xDC8
		BSTOptional<XPChangeData> syncedXPChange;										// 0xDE0
		std::int32_t queuedSwitch : 1;													// 0xDF4:00
		std::uint32_t charGenHUDMode;													// 0xDF8
		bool insideMemoryHUDMode			  : 1;										// 0xDFC:0
		bool xpSyncedWithHUDNotification	  : 1;										// 0xDFC:1
		bool travelUseDoor					  : 1;										// 0xDFC:2
		bool transporting					  : 1;										// 0xDFC:3
		bool overAutoAimTarget				  : 1;										// 0xDFC:4
		bool showQuestItemsInInventory		  : 1;										// 0xDFC:5
		bool hostileDetection				  : 1;										// 0xDFC:6
		bool escaping						  : 1;										// 0xDFC:7
		bool forceQuestTargetRepath			  : 1;										// 0xDFD:0
		bool speaking						  : 1;										// 0xDFD:1
		bool isSleeping						  : 1;										// 0xDFD:2
		bool actorInSneakRange				  : 1;										// 0xDFD:3
		bool greetingPlayer					  : 1;										// 0xDFD:4
		bool beenAttacked					  : 1;										// 0xDFD:5
		bool allowEGMCacheClear				  : 1;										// 0xDFD:6
		bool aiControlledToPos				  : 1;										// 0xDFD:7
		bool aiControlledFromPos			  : 1;										// 0xDFE:0
		bool aiControlledPackage			  : 1;										// 0xDFE:1
		bool returnToLastKnownGoodPosition	  : 1;										// 0xDFE:2
		bool beingChased					  : 1;										// 0xDFE:3
		bool is3rdPersonModelShown			  : 1;										// 0xDFE:4
		bool hideFirstPersonGeometry		  : 1;										// 0xDFE:5
		bool insufficientChargeMessageShownL  : 1;										// 0xDFE:6
		bool insufficientChargeMessageShownR  : 1;										// 0xDFE:7
		bool target3DDistant				  : 1;										// 0xDFF:0
		bool playerInCombat					  : 1;										// 0xDFF:1
		bool attemptedYieldInCurrentCombat	  : 1;										// 0xDFF:2
		bool currentAlchemyIsPoison			  : 1;										// 0xDFF:3
		bool positioning					  : 1;										// 0xDFF:4
		bool crimeReporting					  : 1;										// 0xDFF:5
		bool healthTutorialShown			  : 1;										// 0xDFF:6
		bool magickaTutorialShown			  : 1;										// 0xDFF:7
		bool staminaTutorialShown			  : 1;										// 0xE00:0
		bool goToJailQueued					  : 1;										// 0xE00:1
		bool doorAutosaveQueued				  : 1;										// 0xE00:2
		bool sprintToggled					  : 1;										// 0xE00:3
		bool useHighSpeedLoading			  : 1;										// 0xE00:4
		bool sceneActionActive				  : 1;										// 0xE00:5
		bool sayingHello					  : 1;										// 0xE00:6
		bool disabledRadio					  : 1;										// 0xE00:7
		bool updateAutoAimActor				  : 1;										// 0xE01:0
		bool autoReload						  : 1;										// 0xE01:1
		bool usingScopeWithOverlay			  : 1;										// 0xE01:2
		bool steadyingWeapon				  : 1;										// 0xE01:3
		bool speechChallengeReward			  : 1;										// 0xE01:4
		bool blendOutFirstPersonOffset		  : 1;										// 0xE01:5
		bool dialogueCameraConsiderResume	  : 1;										// 0xE01:6
		bool shouldFollowerSupressIdleChatter : 1;										// 0xE01:7
		bool idleChatter					  : 1;										// 0xE02:0
		bool switchingPerspectives			  : 1;										// 0xE02:1
		bool onElevator						  : 1;										// 0xE02:2
		bool sayCommandResponse				  : 1;										// 0xE02:3
		bool inLooksMenu					  : 1;										// 0xE02:4
		bool playingTimeFrozen				  : 1;										// 0xE02:5
		bool everModded						  : 1;										// 0xE02:6
	};

	static_assert(sizeof(PlayerCharacter) == 0xE10);
}

namespace RE
{
	auto IsPlayerInDialogue() -> bool;
}

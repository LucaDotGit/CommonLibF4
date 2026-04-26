#pragma once

#include "RE//N/NonMorphFaceManagement_InstanceData.hpp"
#include "RE/A/AITimeStamp.hpp"
#include "RE/A/AITimer.hpp"
#include "RE/A/ActorMovementData.hpp"
#include "RE/A/AnimationSpeedInformationTypes_AnimationStateAdjustment.hpp"
#include "RE/B/BGSAnimationSequencer.hpp"
#include "RE/B/BGSAttackData.hpp"
#include "RE/B/BSPathingLocation.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/G/GunStateData.hpp"
#include "RE/I/IDLE_REPLAY_DELAY.hpp"
#include "RE/M/MovementLargeDelta_IdleSelectionData.hpp"
#include "RE/M/Movement_TypedData.hpp"
#include "RE/N/NiBillboardNode.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/ReanimateData.hpp"
#include "RE/T/TESShout.hpp"

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t;
	enum class DEFAULT_OBJECT : std::int32_t;
	enum class PLAYER_ACTION : std::int32_t;

	class ActorKnowledge;
	class AvoidAreaStruct;
	class BSNavmesh;
	class Crime;
	class DetectionEvent;
	class DialogueItem;
	class IAIWorldLocation;
	class PathingRequest;
	class QueuedDialogueType;
	class StandardDetectionListener;

	class HighProcessData
	{
	public:
		enum class VOICE_STATE : std::int32_t
		{
			kNone = 0,
			kRequest = 1,
			kStart = 2,
			kContinue = 3,
			kPrecast = 4,
			kPostcast = 5,
			kFail = 6
		};

		enum class FADE_STATE : std::int32_t
		{
			kNormal = 0,
			kIn = 1,
			kOut = 2,
			kTeleportIn = 3,
			kTeleportOut = 4,
			kOutDisable = 5,
			kOutDelete = 6
		};

		enum class BUMP_TYPE : std::int32_t
		{
			kNone = static_cast<std::underlying_type_t<BUMP_TYPE>>(-1),
			kSmall = 0,
			kBig = 1
		};

		// members
		NonMorphFaceManagement::InstanceData nonMorphChannelsInstance;							  // 000
		GunStateData gunState;																	  // 008
		BSTSmallArray<IDLE_REPLAY_DELAY, 1> replayDelay;										  // 020
		REX::Enum<VOICE_STATE, std::int32_t> voiceState;										  // 040
		TESShout* currentShout;																	  // 048
		REX::Enum<TESShout::VariationID, std::int32_t> currentShoutVariation;					  // 04C
		REX::Float32 voiceTimeElapsed;															  // 050
		REX::Float32 voiceRecoveryTime;															  // 054
		REX::Float32 healthRegenDelay;															  // 058
		REX::Float32 conditionRegenDelay;														  // 05C
		REX::Float32 staminaRegenDelay;															  // 060
		REX::Float32 apRegenDelay;																  // 064
		REX::Float32 radsRegenDelay;															  // 068
		const IAIWorldLocation* sandBoxLocation;												  // 070
		BSTArray<ActorHandle> lastSpokenToArray;												  // 078
		BGSAnimationSequencer animSequencer;													  // 090
		NiPoint3 pathingCurrentMovementSpeed;													  // 0C8
		NiPoint3 pathingCurrentRotationSpeed;													  // 0D4
		NiPoint3 pathingDesiredPosition;														  // 0E0
		NiPoint3 pathingDesiredOrientation;														  // 0EC
		NiPoint3 pathingDesiredMovementSpeed;													  // 0F8
		NiPoint3 pathingDesiredRotationSpeed;													  // 104
		MovementLargeDelta::IdleSelectionData pathingIdleSelectionEnums;						  // 110
		ActorMovementData movementOutput;														  // 120
		REX::Float32 motionFeedbackTimer;														  // 170
		REX::Float32 lastBumpDirection;															  // 174
		ObjectRefHandle lastExtDoorActivated;													  // 178
		REX::Float32 activationHeight;															  // 17C
		ReanimateData myReanimateData;															  // 180
		std::array<std::uint32_t, 3> crca;														  // 190
		Movement::TypeData currentMovementType;													  // 1A0
		REX::Enum<FADE_STATE, std::int32_t> fadeState;											  // 220
		REX::Float32 fadeAlpha;																	  // 224
		TESObjectREFR* teleportFadeRef;															  // 228
		REX::Float32 elevatorFadeTimer;															  // 230
		std::array<ObjectRefHandle, 6> headTrackingTargets;										  // 234
		std::array<bool, 6> headTrackingTargetFlags;											  // 24C
		REX::Float32 headTrackTargetTimer;														  // 254
		NiPoint3 headTrackTargetOffset;															  // 258
		REX::Float32 headTrackHoldOffsetHoldTimer;												  // 264
		REX::Float32 headTrackTargetOffsetTimer;												  // 268
		std::uint32_t eyeTrackHandle;															  // 26C
		ObjectRefHandle lastTarget;																  // 270
		ObjectRefHandle pathLookAtTarget;														  // 274
		BSPathingLocation cachedPathingLocation;												  // 278
		BSNavmesh* cachedPathingLocationNavmesh;												  // 2A8
		mutable BSSpinLock cachedPathingLocationLock;											  // 2B0
		REX::Float32 prevTailPitchChange;														  // 2B8
		REX::Float32 cachedActorHeight;															  // 2BC
		AITimeStamp bumpTimer;																	  // 2C0
		AITimeStamp bumpReactionTimer;															  // 2C4
		REX::Enum<BUMP_TYPE, std::int32_t> bumped;												  // 2C8
		REX::Float32 takeBackTimer;																  // 2CC
		AvoidAreaStruct* avoidAreas;															  // 2D0
		REX::Float32 avoidWaitTimer;															  // 2D8
		REX::Enum<PLAYER_ACTION, std::int32_t> playerActionReactionType;						  // 2DC
		BSFixedStringCS strVoiceSubtitle;														  // 2E0
		BSTArray<BSTPair<std::uint32_t, NiPointer<ActorKnowledge>>> knowledgeArray;				  // 2E8
		mutable BSReadWriteLock knowledgeLock;													  // 300
		BSTArray<QueuedDialogueType*> queueofGreetingsArray;									  // 308
		NiPointer<BGSAttackData> attackData;													  // 320
		NiPoint3 locationOffsetByWaterPoint;													  // 328
		BGSSoundOutput* outputModel;															  // 338
		std::uint32_t activateTopicID;															  // 340
		REX::Float32 distanceSqFromPlayer;														  // 344
		NiPoint3 deathForceDirection;															  // 348
		REX::Float32 deathForce;																  // 354
		REX::Float32 staggerDirection;															  // 358
		REX::Float32 staggerMagnitude;															  // 35C
		REX::Float32 lastAngleToCamera;															  // 360
		REX::Float32 talkTimer;																	  // 364
		REX::Float32 detectListTimer;															  // 368
		REX::Float32 idleChatterTimer;															  // 36C
		REX::Float32 clearTalkToListTimer;														  // 370
		REX::Float32 maxAlpha;																	  // 374
		REX::Float32 packageEvalTimer;															  // 378
		REX::Float32 useItemTimer;																  // 37C
		REX::Float32 procedureEvalTimer;														  // 380
		REX::Float32 checkToTalkTimer;															  // 384
		std::uint32_t randomEventID;															  // 388
		NiNode* node;																			  // 390
		REX::Float32 delayTimer;																  // 398
		REX::Float32 distanceMoved;																  // 39C
		REX::Float32 turnTime;																	  // 3A0
		REX::Float32 evaluateAcquireTimer;														  // 3A4
		std::int16_t lastDetection;																  // 3A8
		NiPoint3 leftWeaponLastPos;																  // 3AC
		NiPoint3 rightWeaponLastPos;															  // 3B8
		ObjectRefHandle greetActor;																  // 3C4
		REX::Float32 soundDelay;																  // 3C8
		std::array<BSSoundHandle, 2> soundHandle;												  // 3CC
		REX::Float32 greetingTimer;																  // 3DC
		REX::Float32 exclusiveTimer;															  // 3E0
		REX::Float32 idleTimer;																	  // 3E4
		REX::Float32 detectGreetTimer;															  // 3E8
		REX::Float32 breathTimer;																  // 3EC
		REX::Float32 voiceTimer;																  // 3F0
		REX::Float32 dyingTimer;																  // 3F4
		REX::Float32 awarePlayerTimer;															  // 3F8
		REX::Float32 helloTimer;																  // 3FC
		TESTopicInfo* lastGreeting;																  // 400
		TESTopicInfo* nextGreeting;																  // 408
		TESIdleForm* idleToPlay;																  // 410
		TESIdleForm* talkIdle;																	  // 418
		BSFixedString loadingDynamicIdleFilename;												  // 420
		ObjectRefHandle idleTarget;																  // 428
		TESPackage* commandPackage;																  // 430
		DialogueItem* greetTopic;																  // 438
		ActorHandle dialogTarget;																  // 440
		void* faceGenGeomHandle;																  // 448
		REX::Float32 scriptPackageEndTime;														  // 450
		const ActorValueInfo* lastCrippleValue;													  // 458
		REX::Float32 healthBarAlphaValue;														  // 460
		NiPointer<NiBillboardNode> healthBarNode;												  // 468
		REX::Float32 actorHealthPercentage;														  // 470
		REX::Float32 healthBarEmittanceValue;													  // 474
		std::int32_t numberGuardsPursuing;														  // 478
		REX::Float32 reEquipArmorTimer;															  // 47C
		BSSimpleList<SpellItem*>* leveledSpellList;												  // 480
		REX::Float32 detectionModifier;															  // 488
		REX::Float32 detectionModifierTimer;													  // 48C
		REX::Float32 lightLevel;																  // 490
		REX::Float32 sceneHeadTrackTimer;														  // 494
		REX::Float32 pCapVoiceFailsafeTimer;													  // 498
		AITimeStamp lightLevelTimeStamp;														  // 49C
		void* lipSynchAnim;																		  // 4A0
		REX::Float32 lipTime;																	  // 4A8
		REX::Float32 activateDoorFailedTimer;													  // 4AC
		std::uint32_t detectionCounter;															  // 4B0
		DetectionEvent* actorsGeneratedDetectionEvent;											  // 4B8
		NiPointer<StandardDetectionListener> detectionListener;									  // 4C0
		AITimer updateDetectionTimer;															  // 4C8
		BSTSmartPointer<PathingRequest> pathingRequest;											  // 4D0
		BSTSmallArray<DEFAULT_OBJECT, 2> queuedActions;											  // 4D8
		BSTArray<AnimationSpeedInformationTypes::AnimationStateAdjustment> queuedAdjustments;	  // 4F0
		BSTArray<AnimationSpeedInformationTypes::AnimationStateAdjustment> lastQueuedAdjustments; // 508
		NiPoint3 animationDelta;																  // 520
		NiPoint3 animationAngleMod;																  // 52C
		REX::Float32 animationUpdateDeltaTime;													  // 538
		REX::Float32 absorbVisualTimer;															  // 53C
		REX::Float32 hitReactionTimer;															  // 540
		REX::Float32 holdFaceTimer;																  // 544
		REX::Float32 tryTalkIdleTimer;															  // 548
		std::uint16_t tryTalk;																	  // 54C
		Crime* crimeToReactTo;																	  // 550
		std::uint8_t lastTurnDir;																  // 558
		std::uint8_t lastTurn;																	  // 559
		std::uint8_t tracerCounter;																  // 55A
		REX::Enum<COMMAND_TYPE, std::int32_t> commandType;										  // 55C
		TESForm* retrieveTarget;																  // 560
		ActorHandle queuedDialogueTarget;														  // 568
		bool processGreetSayTo;																	  // 56C
		bool checkDeadTalk;																		  // 56D
		bool skippedUpdate;																		  // 56E
		bool automaticFireAtLeastOne;															  // 56F
		bool greetingFlag;																		  // 570
		bool pickNewIdle;																		  // 571
		bool skipVoiceEndIdleStop;																  // 572
		bool weaponAlertDrawn;																	  // 573
		bool dialoguewithPlayer;																  // 574
		bool inCommandState;																	  // 575
		bool inWorkShopCommandState;															  // 576
		bool continuingPackageforPC;															  // 577
		bool activateAnim;																		  // 578
		bool stop;																				  // 579
		bool unequippedArmorToSwim;																  // 57A
		bool allowForceReadyWeapon;																  // 57B
		bool activateReady;																		  // 57C
		bool dualCasting;																		  // 57D
		bool plantedExplosive;																	  // 57E
		bool approachingAutoTeleportDoor;														  // 57F
		bool allowDeathForce;																	  // 580
		bool arrested;																			  // 581
		bool forceGreeting;																		  // 582
		bool queuedActivation;																	  // 583
		bool isDoingSayTo;																		  // 584
		bool hiding;																			  // 585
		bool stopShoutAudioManually;															  // 586
		bool farGeometry;																		  // 587
		bool procedureDoesEquip;																  // 588
		bool forceRotate;																		  // 589
		bool speakingDeathLine;																	  // 58A
		bool fistsDrawn;																		  // 58B
		bool freezeGraphLocomotionChannels;														  // 58C
		bool freezeGraphLocomotionEvents;														  // 58D
		bool lastGraphAllowRotation;															  // 58E
		bool lastGraphDriven;																	  // 58F
		bool activateDoor;																		  // 590
		bool startedDialogue;																	  // 591
		bool startingAggroRadius;																  // 592
		bool playerActivated;																	  // 593
		bool itemEquipQueued;																	  // 594
		bool doingCommand;																		  // 595
		bool pCapLineFired;																		  // 596
		bool updateMovementTypeCacheQueued;														  // 597
		bool hasGreetingIdleChatterTicket;														  // 598
		bool processingForceEquip;																  // 599
		bool pCapLinePlaying;																	  // 59A
		bool faceGenLoadPending;																  // 59B
		bool doNotInterruptAnimation;															  // 59C
		bool dialogueInterruptQueued;															  // 59D
		bool pCapLineFailed;																	  // 59E
		bool pathingRequestQuickTurn;															  // 59F
	};
	static_assert(sizeof(HighProcessData) == 0x5A0);
}

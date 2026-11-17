#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/A/AITimer.hpp"
#include "RE/A/ActorMovementData.hpp"
#include "RE/A/AnimationSpeedInformationTypes_AnimationStateAdjustment.hpp"
#include "RE/B/BGSAnimationSequencer.hpp"
#include "RE/B/BGSAttackData.hpp"
#include "RE/B/BSPathingLocation.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSSimpleList.hpp"
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
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NonMorphFaceManagement_InstanceData.hpp"
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
			None = 0,
			Request = 1,
			Start = 2,
			Continue = 3,
			Precast = 4,
			Postcast = 5,
			Fail = 6
		};

		enum class FADE_STATE : std::int32_t
		{
			Normal = 0,
			In = 1,
			Out = 2,
			TeleportIn = 3,
			TeleportOut = 4,
			OutDisable = 5,
			OutDelete = 6
		};

		enum class BUMP_TYPE : std::int32_t
		{
			None = -1,
			Small = 0,
			Big = 1
		};

		// members
		NonMorphFaceManagement::InstanceData nonMorphChannelsInstance;							  // 0x000
		GunStateData gunState;																	  // 0x008
		BSTSmallArray<IDLE_REPLAY_DELAY, 1> replayDelay;										  // 0x020
		REX::Enum<VOICE_STATE, std::int32_t> voiceState;										  // 0x040
		TESShout* currentShout;																	  // 0x048
		REX::Enum<TESShout::VariationID, std::int32_t> currentShoutVariation;					  // 0x04C
		REX::Float32 voiceTimeElapsed;															  // 0x050
		REX::Float32 voiceRecoveryTime;															  // 0x054
		REX::Float32 healthRegenDelay;															  // 0x058
		REX::Float32 conditionRegenDelay;														  // 0x05C
		REX::Float32 staminaRegenDelay;															  // 0x060
		REX::Float32 apRegenDelay;																  // 0x064
		REX::Float32 radsRegenDelay;															  // 0x068
		const IAIWorldLocation* sandBoxLocation;												  // 0x070
		BSTArray<ActorHandle> lastSpokenToArray;												  // 0x078
		BGSAnimationSequencer animSequencer;													  // 0x090
		NiPoint3 pathingCurrentMovementSpeed;													  // 0x0C8
		NiPoint3 pathingCurrentRotationSpeed;													  // 0x0D4
		NiPoint3 pathingDesiredPosition;														  // 0x0E0
		NiPoint3 pathingDesiredOrientation;														  // 0x0EC
		NiPoint3 pathingDesiredMovementSpeed;													  // 0x0F8
		NiPoint3 pathingDesiredRotationSpeed;													  // 0x104
		MovementLargeDelta::IdleSelectionData pathingIdleSelectionEnums;						  // 0x110
		ActorMovementData movementOutput;														  // 0x120
		REX::Float32 motionFeedbackTimer;														  // 0x170
		REX::Float32 lastBumpDirection;															  // 0x174
		ObjectRefHandle lastExtDoorActivated;													  // 0x178
		REX::Float32 activationHeight;															  // 0x17C
		ReanimateData myReanimateData;															  // 0x180
		std::array<std::uint32_t, 3> crca;														  // 0x190
		Movement::TypeData currentMovementType;													  // 0x1A0
		REX::Enum<FADE_STATE, std::int32_t> fadeState;											  // 0x220
		REX::Float32 fadeAlpha;																	  // 0x224
		TESObjectREFR* teleportFadeRef;															  // 0x228
		REX::Float32 elevatorFadeTimer;															  // 0x230
		std::array<ObjectRefHandle, 6> headTrackingTargets;										  // 0x234
		std::array<bool, 6> headTrackingTargetFlags;											  // 0x24C
		REX::Float32 headTrackTargetTimer;														  // 0x254
		NiPoint3 headTrackTargetOffset;															  // 0x258
		REX::Float32 headTrackHoldOffsetHoldTimer;												  // 0x264
		REX::Float32 headTrackTargetOffsetTimer;												  // 0x268
		std::uint32_t eyeTrackHandle;															  // 0x26C
		ObjectRefHandle lastTarget;																  // 0x270
		ObjectRefHandle pathLookAtTarget;														  // 0x274
		BSPathingLocation cachedPathingLocation;												  // 0x278
		BSNavmesh* cachedPathingLocationNavmesh;												  // 0x2A8
		mutable BSSpinLock cachedPathingLocationLock;											  // 0x2B0
		REX::Float32 prevTailPitchChange;														  // 0x2B8
		REX::Float32 cachedActorHeight;															  // 0x2BC
		AITimeStamp bumpTimer;																	  // 0x2C0
		AITimeStamp bumpReactionTimer;															  // 0x2C4
		REX::Enum<BUMP_TYPE, std::int32_t> bumped;												  // 0x2C8
		REX::Float32 takeBackTimer;																  // 0x2CC
		AvoidAreaStruct* avoidAreas;															  // 0x2D0
		REX::Float32 avoidWaitTimer;															  // 0x2D8
		REX::Enum<PLAYER_ACTION, std::int32_t> playerActionReactionType;						  // 0x2DC
		BSFixedStringCS strVoiceSubtitle;														  // 0x2E0
		BSTArray<BSTPair<std::uint32_t, NiPointer<ActorKnowledge>>> knowledgeArray;				  // 0x2E8
		mutable BSReadWriteLock knowledgeLock;													  // 0x300
		BSTArray<QueuedDialogueType*> queueofGreetingsArray;									  // 0x308
		NiPointer<BGSAttackData> attackData;													  // 0x320
		NiPoint3 locationOffsetByWaterPoint;													  // 0x328
		BGSSoundOutput* outputModel;															  // 0x338
		std::uint32_t activateTopicID;															  // 0x340
		REX::Float32 distanceSqFromPlayer;														  // 0x344
		NiPoint3 deathForceDirection;															  // 0x348
		REX::Float32 deathForce;																  // 0x354
		REX::Float32 staggerDirection;															  // 0x358
		REX::Float32 staggerMagnitude;															  // 0x35C
		REX::Float32 lastAngleToCamera;															  // 0x360
		REX::Float32 talkTimer;																	  // 0x364
		REX::Float32 detectListTimer;															  // 0x368
		REX::Float32 idleChatterTimer;															  // 0x36C
		REX::Float32 clearTalkToListTimer;														  // 0x370
		REX::Float32 maxAlpha;																	  // 0x374
		REX::Float32 packageEvalTimer;															  // 0x378
		REX::Float32 useItemTimer;																  // 0x37C
		REX::Float32 procedureEvalTimer;														  // 0x380
		REX::Float32 checkToTalkTimer;															  // 0x384
		std::uint32_t randomEventID;															  // 0x388
		NiNode* node;																			  // 0x390
		REX::Float32 delayTimer;																  // 0x398
		REX::Float32 distanceMoved;																  // 0x39C
		REX::Float32 turnTime;																	  // 0x3A0
		REX::Float32 evaluateAcquireTimer;														  // 0x3A4
		std::int16_t lastDetection;																  // 0x3A8
		NiPoint3 leftWeaponLastPos;																  // 0x3AC
		NiPoint3 rightWeaponLastPos;															  // 0x3B8
		ObjectRefHandle greetActor;																  // 0x3C4
		REX::Float32 soundDelay;																  // 0x3C8
		std::array<BSSoundHandle, 2> soundHandle;												  // 0x3CC
		REX::Float32 greetingTimer;																  // 0x3DC
		REX::Float32 exclusiveTimer;															  // 0x3E0
		REX::Float32 idleTimer;																	  // 0x3E4
		REX::Float32 detectGreetTimer;															  // 0x3E8
		REX::Float32 breathTimer;																  // 0x3EC
		REX::Float32 voiceTimer;																  // 0x3F0
		REX::Float32 dyingTimer;																  // 0x3F4
		REX::Float32 awarePlayerTimer;															  // 0x3F8
		REX::Float32 helloTimer;																  // 0x3FC
		TESTopicInfo* lastGreeting;																  // 0x400
		TESTopicInfo* nextGreeting;																  // 0x408
		TESIdleForm* idleToPlay;																  // 0x410
		TESIdleForm* talkIdle;																	  // 0x418
		BSFixedString loadingDynamicIdleFilename;												  // 0x420
		ObjectRefHandle idleTarget;																  // 0x428
		TESPackage* commandPackage;																  // 0x430
		DialogueItem* greetTopic;																  // 0x438
		ActorHandle dialogTarget;																  // 0x440
		void* faceGenGeomHandle;																  // 0x448
		REX::Float32 scriptPackageEndTime;														  // 0x450
		const ActorValueInfo* lastCrippleValue;													  // 0x458
		REX::Float32 healthBarAlphaValue;														  // 0x460
		NiPointer<NiBillboardNode> healthBarNode;												  // 0x468
		REX::Float32 actorHealthPercentage;														  // 0x470
		REX::Float32 healthBarEmittanceValue;													  // 0x474
		std::int32_t numberGuardsPursuing;														  // 0x478
		REX::Float32 reEquipArmorTimer;															  // 0x47C
		BSSimpleList<SpellItem*>* leveledSpellList;												  // 0x480
		REX::Float32 detectionModifier;															  // 0x488
		REX::Float32 detectionModifierTimer;													  // 0x48C
		REX::Float32 lightLevel;																  // 0x490
		REX::Float32 sceneHeadTrackTimer;														  // 0x494
		REX::Float32 pCapVoiceFailsafeTimer;													  // 0x498
		AITimeStamp lightLevelTimeStamp;														  // 0x49C
		void* lipSynchAnim;																		  // 0x4A0
		REX::Float32 lipTime;																	  // 0x4A8
		REX::Float32 activateDoorFailedTimer;													  // 0x4AC
		std::uint32_t detectionCounter;															  // 0x4B0
		DetectionEvent* actorsGeneratedDetectionEvent;											  // 0x4B8
		NiPointer<StandardDetectionListener> detectionListener;									  // 0x4C0
		AITimer updateDetectionTimer;															  // 0x4C8
		BSTSmartPointer<PathingRequest> pathingRequest;											  // 0x4D0
		BSTSmallArray<DEFAULT_OBJECT, 2> queuedActions;											  // 0x4D8
		BSTArray<AnimationSpeedInformationTypes::AnimationStateAdjustment> queuedAdjustments;	  // 0x4F0
		BSTArray<AnimationSpeedInformationTypes::AnimationStateAdjustment> lastQueuedAdjustments; // 0x508
		NiPoint3 animationDelta;																  // 0x520
		NiPoint3 animationAngleMod;																  // 0x52C
		REX::Float32 animationUpdateDeltaTime;													  // 0x538
		REX::Float32 absorbVisualTimer;															  // 0x53C
		REX::Float32 hitReactionTimer;															  // 0x540
		REX::Float32 holdFaceTimer;																  // 0x544
		REX::Float32 tryTalkIdleTimer;															  // 0x548
		std::uint16_t tryTalk;																	  // 0x54C
		Crime* crimeToReactTo;																	  // 0x550
		std::uint8_t lastTurnDir;																  // 0x558
		std::uint8_t lastTurn;																	  // 0x559
		std::uint8_t tracerCounter;																  // 0x55A
		REX::Enum<COMMAND_TYPE, std::int32_t> commandType;										  // 0x55C
		TESForm* retrieveTarget;																  // 0x560
		ActorHandle queuedDialogueTarget;														  // 0x568
		bool processGreetSayTo;																	  // 0x56C
		bool checkDeadTalk;																		  // 0x56D
		bool skippedUpdate;																		  // 0x56E
		bool automaticFireAtLeastOne;															  // 0x56F
		bool greetingFlag;																		  // 0x570
		bool pickNewIdle;																		  // 0x571
		bool skipVoiceEndIdleStop;																  // 0x572
		bool weaponAlertDrawn;																	  // 0x573
		bool dialogueWithPlayer;																  // 0x574
		bool inCommandState;																	  // 0x575
		bool inWorkShopCommandState;															  // 0x576
		bool continuingPackageforPC;															  // 0x577
		bool activateAnim;																		  // 0x578
		bool stop;																				  // 0x579
		bool unequippedArmorToSwim;																  // 0x57A
		bool allowForceReadyWeapon;																  // 0x57B
		bool activateReady;																		  // 0x57C
		bool dualCasting;																		  // 0x57D
		bool plantedExplosive;																	  // 0x57E
		bool approachingAutoTeleportDoor;														  // 0x57F
		bool allowDeathForce;																	  // 0x580
		bool arrested;																			  // 0x581
		bool forceGreeting;																		  // 0x582
		bool queuedActivation;																	  // 0x583
		bool isDoingSayTo;																		  // 0x584
		bool hiding;																			  // 0x585
		bool stopShoutAudioManually;															  // 0x586
		bool farGeometry;																		  // 0x587
		bool procedureDoesEquip;																  // 0x588
		bool forceRotate;																		  // 0x589
		bool speakingDeathLine;																	  // 0x58A
		bool fistsDrawn;																		  // 0x58B
		bool freezeGraphLocomotionChannels;														  // 0x58C
		bool freezeGraphLocomotionEvents;														  // 0x58D
		bool lastGraphAllowRotation;															  // 0x58E
		bool lastGraphDriven;																	  // 0x58F
		bool activateDoor;																		  // 0x590
		bool startedDialogue;																	  // 0x591
		bool startingAggroRadius;																  // 0x592
		bool playerActivated;																	  // 0x593
		bool itemEquipQueued;																	  // 0x594
		bool doingCommand;																		  // 0x595
		bool pCapLineFired;																		  // 0x596
		bool updateMovementTypeCacheQueued;														  // 0x597
		bool hasGreetingIdleChatterTicket;														  // 0x598
		bool processingForceEquip;																  // 0x599
		bool pCapLinePlaying;																	  // 0x59A
		bool faceGenLoadPending;																  // 0x59B
		bool doNotInterruptAnimation;															  // 0x59C
		bool dialogueInterruptQueued;															  // 0x59D
		bool pCapLineFailed;																	  // 0x59E
		bool pathingRequestQuickTurn;															  // 0x59F
	};

	static_assert(sizeof(HighProcessData) == 0x5A0);
}

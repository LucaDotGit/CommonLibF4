#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/A/ActiveEffectList.hpp"
#include "RE/A/ActorPackage.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SubgraphHandle.hpp"
#include "RE/S/SubgraphIdentifier.hpp"

namespace RE::MagicSystem
{
	enum class WardState : std::int32_t;
}

namespace RE
{
	enum class PACKAGE_OBJECT_TYPE : std::int32_t;

	class ActorInventoryEvent;
	class AIPerkData;
	class bhkCharacterController;
	class bhkNPCollisionObject;
	class bhkRagdollPenetrationUtil;
	class BSAnimationGraphManager;
	class BSAnimationGraphVariableCache;
	class BSClothExtraData;
	class BSFaceGenAnimationData;
	class BSFaceGenNiNode;
	class BSLightingShaderProperty;
	class CommandedActorData;
	class DeferredHideLimb;
	class EquippedItem;
	class HitData;
	class IAnimationStanceData;
	class NiAVObject;
	class NiNode;
	class QueuedFile;
	class QueuedItem;
	class SubGraphIdleRootData;

	class MiddleHighProcessData
	{
	public:
		// members
		BSTEventSource<ActorInventoryEvent> inventoryEventSource;		  // 000
		NiPointer<bhkNPCollisionObject> poseBound;						  // 058
		ActorPackage runOncePackage;									  // 060
		BSTArray<ActorHandle> deadDetectList;							  // 090
		BSSimpleList<TESObjectREFR*> refListChairBed;					  // 0A8
		NiPoint3 rotation;												  // 0B8
		NiPoint3 rotationSpeed;											  // 0C4
		NiPoint3 actorMountPosition;									  // 0D0
		NiPoint3 furniturePathPoint;									  // 0DC
		NiPoint3 lastSeenPosition;										  // 0E8
		ActorHandle bleedoutAttacker;									  // 0F4
		REX::Enum<MagicSystem::WardState, std::int32_t> wardState;		  // 0F8
		BSTSmartPointer<void*> animResponse;							  // 100 - TODO: `BSResponse<BSFixedString, Actor, BSFixedString, DoNothingUnhandledPolicy>`
		BSTArray<CommandedActorData> commandedActors;					  // 108
		std::array<NiNode*, 26> damageRootNode;							  // 120
		NiNode* weaponBone;												  // 1F0
		NiAVObject* headNode;											  // 1F8
		NiAVObject* torsoNode;											  // 200
		NiAVObject* faceTargetSourceNode;								  // 208
		BSFaceGenNiNode* faceNodeSkinned;								  // 210
		NiPointer<BSLightingShaderProperty> lightingProperty;			  // 218
		QueuedItem* listItemstoEquipUnequip;							  // 220
		HitData* lastHitData;											  // 228
		DeferredHideLimb* headDeferredHideLimb;							  // 230
		ActiveEffectList activeEffects;									  // 238
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;	  // 258
		BSAnimationGraphVariableCache* animationVariableCache;			  // 260
		BSTArray<SubGraphIdleRootData> subGraphIdleManagerRoots;		  // 268
		mutable BSSpinLock equippedItemsLock;							  // 280
		BSTArray<EquippedItem> equippedItems;							  // 288
		BSTArray<BSClothExtraData*> clothExtraDataCache;				  // 2A0
		BSTArray<BSTSmallArray<SubgraphHandle, 2>> subGraphHandles;		  // 2B8
		BSTSmallArray<SubgraphIdentifier, 2> currentDefaultSubGraphID;	  // 2D0
		BSTSmallArray<SubgraphIdentifier, 2> requestedDefaultSubGraphID;  // 2F0
		BSTSmallArray<SubgraphIdentifier, 2> currentWeaponSubGraphID;	  // 310
		BSTSmallArray<SubgraphIdentifier, 2> requestedWeaponSubGraphID;	  // 330
		BSTSmartPointer<IAnimationStanceData> stanceData;				  // 350
		BSTArray<BSTPair<std::uint32_t, void*>> nodeLocationArray;		  // 358 - TODO: `AnimationStanceNodeLocationData<NiPoint3>`
		std::array<std::array<REX::Float32, 6>, 2> stanceHeightArray;	  // 370
		REX::Float32 headHeightOffset;									  // 3A0
		ObjectRefHandle currentFurniture;								  // 3A4
		ObjectRefHandle occupiedFurniture;								  // 3A8
		TESIdleForm* currentIdle;										  // 3B0
		ActorHandle commandingActor;									  // 3B8
		TESIdleForm* furnitureIdle;										  // 3C0
		BSFaceGenAnimationData* faceAnimationData;						  // 3C8
		MagicItem* currentPackageSpell;									  // 3D0
		TESObjectWEAP* lastBoundWeapon;									  // 3D8
		NiPointer<bhkCharacterController> charController;				  // 3E0
		BSTSmartPointer<bhkRagdollPenetrationUtil> penetrationDetectUtil; // 3E8
		NiPointer<QueuedFile> bodyPartPreload;							  // 3F0
		TESIdleForm* lastIdlePlayed;									  // 3F8
		AIPerkData* perkData;											  // 400
		NiPoint3 lookAtLocation;										  // 408
		REX::Float32 pursueTimer;										  // 414
		REX::Float32 furnitureAngle;									  // 418
		REX::Float32 furnitureEntryFootstepDeltaTarget;					  // 41C
		REX::Float32 packageIdleTimer;									  // 420
		REX::Float32 equippedWeight;									  // 424
		REX::Float32 desiredSpeed;										  // 428
		REX::Float32 animationSpeed;									  // 42C
		REX::Float32 bleedoutTimer;										  // 430
		REX::Float32 bleedoutRate;										  // 434
		REX::Float32 bleedoutMaxHealth;									  // 438
		REX::Float32 maxWardPower;										  // 43C
		REX::Float32 animGraphEventTimeout;								  // 440
		REX::Float32 torchEvalTimer;									  // 444
		REX::Float32 alphaMult;											  // 448
		REX::Float32 scriptRefractPower;								  // 44C
		REX::Float32 sleepingTimer;										  // 450
		REX::Float32 deferredKillTimer;									  // 454
		REX::Float32 killMoveTimer;										  // 458
		REX::Float32 staggerTimer;										  // 45C
		REX::Float32 mountDismountSafetyTimer;							  // 460
		AITimeStamp rangeWaypointIdleTimer;								  // 464
		std::int32_t packageIdleNumber;									  // 468
		std::int32_t reservationSlot;									  // 46C
		SubgraphIdentifier currentFurnitureSubgraphID;					  // 470
		std::uint32_t currentFurnitureMarkerID;							  // 478
		std::uint32_t occupiedFurnitureMarkerID;						  // 47C
		std::uint64_t nextExtraArrow3DUpdate;							  // 480
		std::uint32_t deferredKill;										  // 488
		std::uint32_t flareFlags;										  // 48C
		REX::Enum<PACKAGE_OBJECT_TYPE, std::int32_t> useItem;			  // 490
		std::int16_t animActionSuccess;									  // 494
		std::uint16_t update3DModel;									  // 496
		std::int8_t weaponCullCounter;									  // 498
		std::int8_t archetypeChangeType;								  // 499
		bool animWeaponCull;											  // 49A
		bool aimingTarget;												  // 49B
		bool doneClothesChange;											  // 49C
		bool pickPackIdle;												  // 49D
		bool doneOnce;													  // 49E
		bool refreshFlareFlags;											  // 49F
		bool pickPocketed;												  // 4A0
		bool summonedCreature;											  // 4A1
		bool forceNextUpdate;											  // 4A2
		bool playedBeginIdles;											  // 4A3
		bool playedEndIdles;											  // 4A4
		bool quickPlacement;											  // 4A5
		bool beenAttacked;												  // 4A6
		bool alwaysHit;													  // 4A7
		bool doNoDamage;												  // 4A8
		bool soulTrapped;												  // 4A9
		bool lookAt;													  // 4AA
		bool eating;													  // 4AB
		bool calcLight;													  // 4AC
		bool preventCombat;												  // 4AD
		bool dyingFromBleedout;											  // 4AE
		bool fleeing;													  // 4AF
		bool instantGetOut;												  // 4B0
		bool hostileGuard;												  // 4B1
		bool stopIdleFailed;											  // 4B2
		bool killQueued;												  // 4B3
		bool ragdollInstant;											  // 4B4
		bool scriptDeferredKill;										  // 4B5
		bool furnitureEntryLeftFootFirst;								  // 4B6
		bool furnitureAnimationPlayed;									  // 4B7
		bool queuedInstantInteractionAnimation;							  // 4B8
		bool queuedModifyInitialAnimationPose;							  // 4B9
		bool avoidPlayer;												  // 4BA
		bool usingPathingFaceTargetWhileTrackingOutOfRange;				  // 4BB
	};
	static_assert(sizeof(MiddleHighProcessData) == 0x4C0);
}

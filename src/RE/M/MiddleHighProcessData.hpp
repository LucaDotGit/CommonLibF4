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
#include "RE/N/NiPoint3.hpp"
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
		BSTEventSource<ActorInventoryEvent> inventoryEventSource;  // 0x000
		NiPointer<bhkNPCollisionObject> poseBound;				   // 0x058
		ActorPackage runOncePackage;							   // 0x060
		BSTArray<ActorHandle> deadDetectList;					   // 0x090
		BSSimpleList<TESObjectREFR*> refListChairBed;			   // 0x0A8
		NiPoint3 rotation;										   // 0x0B8
		NiPoint3 rotationSpeed;									   // 0x0C4
		NiPoint3 actorMountPosition;							   // 0x0D0
		NiPoint3 furniturePathPoint;							   // 0x0DC
		NiPoint3 lastSeenPosition;								   // 0x0E8
		ActorHandle bleedoutAttacker;							   // 0x0F4
		REX::Enum<MagicSystem::WardState, std::int32_t> wardState; // 0x0F8
		BSTSmartPointer<void*>
			animResponse; // 0x100 - To-Do: `BSResponse<BSFixedString, Actor, BSFixedString, DoNothingUnhandledPolicy>`
		BSTArray<CommandedActorData> commandedActors;					 // 0x108
		std::array<NiNode*, 26> damageRootNode;							 // 0x120
		NiNode* weaponBone;												 // 0x1F0
		NiAVObject* headNode;											 // 0x1F8
		NiAVObject* torsoNode;											 // 0x200
		NiAVObject* faceTargetSourceNode;								 // 0x208
		BSFaceGenNiNode* faceNodeSkinned;								 // 0x210
		NiPointer<BSLightingShaderProperty> lightingProperty;			 // 0x218
		QueuedItem* listItemstoEquipUnequip;							 // 0x220
		HitData* lastHitData;											 // 0x228
		DeferredHideLimb* headDeferredHideLimb;							 // 0x230
		ActiveEffectList activeEffects;									 // 0x238
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;	 // 0x258
		BSAnimationGraphVariableCache* animationVariableCache;			 // 0x260
		BSTArray<SubGraphIdleRootData> subGraphIdleManagerRoots;		 // 0x268
		mutable BSSpinLock equippedItemsLock;							 // 0x280
		BSTArray<EquippedItem> equippedItems;							 // 0x288
		BSTArray<BSClothExtraData*> clothExtraDataCache;				 // 0x2A0
		BSTArray<BSTSmallArray<SubgraphHandle, 2>> subGraphHandles;		 // 0x2B8
		BSTSmallArray<SubgraphIdentifier, 2> currentDefaultSubGraphID;	 // 0x2D0
		BSTSmallArray<SubgraphIdentifier, 2> requestedDefaultSubGraphID; // 0x2F0
		BSTSmallArray<SubgraphIdentifier, 2> currentWeaponSubGraphID;	 // 0x310
		BSTSmallArray<SubgraphIdentifier, 2> requestedWeaponSubGraphID;	 // 0x330
		BSTSmartPointer<IAnimationStanceData> stanceData;				 // 0x350
		BSTArray<BSTPair<std::uint32_t, void*>>
			nodeLocationArray; // 0x358 - To-Do: `AnimationStanceNodeLocationData<NiPoint3>`
		std::array<std::array<REX::Float32, 6>, 2> stanceHeightArray;	  // 0x370
		REX::Float32 headHeightOffset;									  // 0x3A0
		ObjectRefHandle currentFurniture;								  // 0x3A4
		ObjectRefHandle occupiedFurniture;								  // 0x3A8
		TESIdleForm* currentIdle;										  // 0x3B0
		ActorHandle commandingActor;									  // 0x3B8
		TESIdleForm* furnitureIdle;										  // 0x3C0
		BSFaceGenAnimationData* faceAnimationData;						  // 0x3C8
		MagicItem* currentPackageSpell;									  // 0x3D0
		TESObjectWEAP* lastBoundWeapon;									  // 0x3D8
		NiPointer<bhkCharacterController> charController;				  // 0x3E0
		BSTSmartPointer<bhkRagdollPenetrationUtil> penetrationDetectUtil; // 0x3E8
		NiPointer<QueuedFile> bodyPartPreload;							  // 0x3F0
		TESIdleForm* lastIdlePlayed;									  // 0x3F8
		AIPerkData* perkData;											  // 0x400
		NiPoint3 lookAtLocation;										  // 0x408
		REX::Float32 pursueTimer;										  // 0x414
		REX::Float32 furnitureAngle;									  // 0x418
		REX::Float32 furnitureEntryFootstepDeltaTarget;					  // 0x41C
		REX::Float32 packageIdleTimer;									  // 0x420
		REX::Float32 equippedWeight;									  // 0x424
		REX::Float32 desiredSpeed;										  // 0x428
		REX::Float32 animationSpeed;									  // 0x42C
		REX::Float32 bleedoutTimer;										  // 0x430
		REX::Float32 bleedoutRate;										  // 0x434
		REX::Float32 bleedoutMaxHealth;									  // 0x438
		REX::Float32 maxWardPower;										  // 0x43C
		REX::Float32 animGraphEventTimeout;								  // 0x440
		REX::Float32 torchEvalTimer;									  // 0x444
		REX::Float32 alphaMult;											  // 0x448
		REX::Float32 scriptRefractPower;								  // 0x44C
		REX::Float32 sleepingTimer;										  // 0x450
		REX::Float32 deferredKillTimer;									  // 0x454
		REX::Float32 killMoveTimer;										  // 0x458
		REX::Float32 staggerTimer;										  // 0x45C
		REX::Float32 mountDismountSafetyTimer;							  // 0x460
		AITimeStamp rangeWaypointIdleTimer;								  // 0x464
		std::int32_t packageIdleNumber;									  // 0x468
		std::int32_t reservationSlot;									  // 0x46C
		SubgraphIdentifier currentFurnitureSubgraphID;					  // 0x470
		std::uint32_t currentFurnitureMarkerID;							  // 0x478
		std::uint32_t occupiedFurnitureMarkerID;						  // 0x47C
		std::uint64_t nextExtraArrow3DUpdate;							  // 0x480
		std::uint32_t deferredKill;										  // 0x488
		std::uint32_t flareFlags;										  // 0x48C
		REX::Enum<PACKAGE_OBJECT_TYPE, std::int32_t> useItem;			  // 0x490
		std::int16_t animActionSuccess;									  // 0x494
		std::uint16_t update3DModel;									  // 0x496
		std::int8_t weaponCullCounter;									  // 0x498
		std::int8_t archetypeChangeType;								  // 0x499
		bool animWeaponCull;											  // 0x49A
		bool aimingTarget;												  // 0x49B
		bool doneClothesChange;											  // 0x49C
		bool pickPackIdle;												  // 0x49D
		bool doneOnce;													  // 0x49E
		bool refreshFlareFlags;											  // 0x49F
		bool pickPocketed;												  // 0x4A0
		bool summonedCreature;											  // 0x4A1
		bool forceNextUpdate;											  // 0x4A2
		bool playedBeginIdles;											  // 0x4A3
		bool playedEndIdles;											  // 0x4A4
		bool quickPlacement;											  // 0x4A5
		bool beenAttacked;												  // 0x4A6
		bool alwaysHit;													  // 0x4A7
		bool doNoDamage;												  // 0x4A8
		bool soulTrapped;												  // 0x4A9
		bool lookAt;													  // 0x4AA
		bool eating;													  // 0x4AB
		bool calcLight;													  // 0x4AC
		bool preventCombat;												  // 0x4AD
		bool dyingFromBleedout;											  // 0x4AE
		bool fleeing;													  // 0x4AF
		bool instantGetOut;												  // 0x4B0
		bool hostileGuard;												  // 0x4B1
		bool stopIdleFailed;											  // 0x4B2
		bool killQueued;												  // 0x4B3
		bool ragdollInstant;											  // 0x4B4
		bool scriptDeferredKill;										  // 0x4B5
		bool furnitureEntryLeftFootFirst;								  // 0x4B6
		bool furnitureAnimationPlayed;									  // 0x4B7
		bool queuedInstantInteractionAnimation;							  // 0x4B8
		bool queuedModifyInitialAnimationPose;							  // 0x4B9
		bool avoidPlayer;												  // 0x4BA
		bool usingPathingFaceTargetWhileTrackingOutOfRange;				  // 0x4BB
	};

	static_assert(sizeof(MiddleHighProcessData) == 0x4C0);
}

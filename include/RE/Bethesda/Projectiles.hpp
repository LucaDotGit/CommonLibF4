#pragma once

#include "RE/Bethesda/BGSBodyPartDefs.hpp"
#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSSoundHandle.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/CELLJobs.hpp"
#include "RE/Bethesda/TESObjectREFRs.hpp"
#include "RE/NetImmerse/NiPoint.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"
#include "RE/NetImmerse/NiTransform.hpp"

namespace RE
{
	enum class COL_LAYER
	{
		kUnidentified = 0,
		kStatic = 1,
		kAnimStatic = 2,
		kTransparent = 3,
		kClutter = 4,
		kWeapon = 5,
		kProjectile = 6,
		kSpell = 7,
		kBiped = 8,
		kTrees = 9,
		kProps = 10,
		kWater = 11,
		kTrigger = 12,
		kTerrain = 13,
		kTrap = 14,
		kNonCollidable = 15,
		kCloudTrap = 16,
		kGround = 17,
		kPortal = 18,
		kDebrisSmall = 19,
		kDebrisLarge = 20,
		kAcousticSpace = 21,
		kActorZone = 22,
		kProjectileZone = 23,
		kGasTrap = 24,
		kShellCasting = 25,
		kTransparentWall = 26,
		kInvisibleWall = 27,
		kTransparentSmallAnim = 28,
		kClutterLarge = 29,
		kCharController = 30,
		kStairHelper = 31,
		kDeadBip = 32,
		kBipedNoCC = 33,
		kAvoidBox = 34,
		kCollisionBox = 35,
		kCameraSphere = 36,
		kDoorDetection = 37,
		kConeProjectile = 38,
		kCamera = 39,
		kItemPicker = 40,
		kLOS = 41,
		kPathingPick = 42,
		kUnused0 = 43,
		kUnused1 = 44,
		kSpellExplosion = 45,
		kDroppingPick = 46
	};

	enum class ImpactResult
	{
		kNone = 0,
		kDestroy = 1,
		kBounce = 2,
		kImpale = 3,
		kStick = 4
	};

	class ActorCause;
	class bhkNPCollisionObject;
	class BSMagicShaderParticles;
	class BSProceduralGeomEvent;
	class EffectSetting;
	class hknpShape;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class QueuedFile;

	struct BeamProjectileImpactEvent;

	struct bhkCollisionQueryResultHandle
	{
	public:
		// members
		std::uint64_t data; // 00
	};
	static_assert(sizeof(bhkCollisionQueryResultHandle) == 0x8);

	class __declspec(novtable) Projectile
		: public TESObjectREFR // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Projectile };
		inline static constexpr auto VTABLE{ VTABLE::Projectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kREFR };

		struct ImpactCreation;

		class ImpactData
		{
		public:
			// members
			NiPoint3 location;									   // 00
			NiPoint3 normal;									   // 0C
			bhkCollisionQueryResultHandle impactDecalQuery;		   // 18
			ObjectRefHandle collidee;							   // 20
			NiPointer<bhkNPCollisionObject> colObj;				   // 28
			BGSMaterialType* materialType;						   // 30
			BGSBodyPartDefs::LIMB_ENUM damageLimb;				   // 38
			REX::Enum<COL_LAYER, std::int32_t> collisionLayer;	   // 3C
			NiPointer<NiNode> closestBone;						   // 40
			REX::Enum<ImpactResult, std::uint32_t> resultOverride; // 48
			float decalSize;									   // 4C
			std::uint32_t collisionShapeKey;					   // 50
			std::int16_t targetWorldObjectCount;				   // 54
			std::int16_t targetWorldObjectIndex;				   // 56
			bool processed;										   // 58
			bool spellCast;										   // 59
			bool effectSpawned;									   // 5A
			bool backface;										   // 5B
		};
		static_assert(sizeof(ImpactData) == 0x60);

		// add
		virtual bool IsMissileProjectile() const { return false; }														// C6
		virtual bool IsGrenadeProjectile() const { return false; }														// C7
		virtual bool IsFlameProjectile() const { return false; }														// C8
		virtual bool IsBeamProjectile() const { return false; }															// C9
		virtual bool IsFogProjectile() const { return false; }															// CA
		virtual bool IsBarrierProjectile() const { return false; }														// CB
		virtual void OnKill() { return; }																				// CC
		virtual void Process3D() { return; }																			// CD
		virtual void PostLoad3D(NiAVObject* a_obj3D);																	// CE
		virtual void UpdateImpl(float a_delta) = 0;																		// CF
		virtual bool ProcessImpacts();																					// D0
		virtual void Update3D(CELLJobs::AnimatedRefJobData* a_data);													// D1
		virtual bool IsMine() const { return false; }																	// D2
		virtual float GetPowerSpeedMult() const { return spell ? 1.0F : power; }										// D3
		virtual float GetWeaponSpeedMult() const { return 1.0F; }														// D4
		virtual bool GetStopMainSoundAfterImpact() const { return false; }												// D5
		virtual void ReportHavokDeactivation() { return; }																// D6
		virtual bool TurnOff(Actor* a_actionActor, bool a_silent);														// D7
		virtual bool IsPermanent();																						// D8
		virtual float GetGravity() const;																				// D9
		virtual void CleanUpPointersOnDisable();																		// DA
		virtual bool RunTargetPick();																					// DB
		virtual bool GetKillOnCollision() const { return true; }														// DC
		virtual bool ShouldBeLimited() const { return false; }															// DD
		virtual bool TargetsWholeBody() const { return false; }															// DE
		virtual bool GetAllowMovement() const;																			// DF
		virtual std::uint32_t GetCollisionGroup() const;																// E0
		virtual hknpShape* GetCollisionShape();																			// E1
		virtual void InitializeImpl() { return; }																		// E2
		virtual void Relaunch() { return; }																				// E3
		virtual std::uint32_t AddImpact(const ImpactCreation& a_data);													// E4
		virtual bool HandleHits(const hknpAllHitsCollector& a_collector, const NiPoint3& a_from, const NiPoint3& a_to); // E5
		virtual void OnEnterTrigger() { return; }																		// E6
		virtual void AddInitialVelocity();																				// E7
		virtual void Handle3DLoaded() { return; }																		// E8
		virtual bool ShouldUseDesiredTarget() { return false; }															// E9

		// members
		BSTArray<ImpactData> impacts;					 // 110
		NiTransform followOffset;						 // 130
		NiPointer<bhkNPCollisionObject> collisionObject; // 170
		NiPointer<TESObjectREFR> droppedRefr;			 // 178
		NiPoint3 movementDirection;						 // 180
		NiPoint3 velocity;								 // 18C
		NiPointer<NiLight> light;						 // 198
		NiPointer<ActorCause> actorCause;				 // 1A0
		ObjectRefHandle shooter;						 // 1A8
		ObjectRefHandle desiredTarget;					 // 1AC
		BSSoundHandle sndHandle;						 // 1B0
		BSSoundHandle sndCountdown;						 // 1B8
		BGSExplosion* explosion;						 // 1C0
		MagicItem* spell;								 // 1C8
		MagicSystem::CastingSource castingSource;		 // 1D0
		EffectSetting* avEffect;						 // 1D8
		NiPointer<QueuedFile> projectileDBFiles;		 // 1E0
		void* muzzleFlashDBHandle;						 // 1E8 - To-Do
		NiPointer<NiNode> muzzleFlashArt;				 // 1F0
		BSMagicShaderParticles* particles;				 // 1F8
		BGSBodyPartDefs::LIMB_ENUM targetLimb;			 // 200
		NiPointer<NiAVObject> targetLimbObj;			 // 208
		NiAVObject* clonePoolKey;						 // 210
		float power;									 // 218
		float speedMult;								 // 21C
		float range;									 // 220
		float age;										 // 224
		float damage;									 // 228
		float alpha;									 // 22C
		float explosionTimer;							 // 230
		float blinkTimer;								 // 234
		BGSObjectInstanceT<TESObjectWEAP> weaponSource;	 // 238
		TESAmmo* ammoSource;							 // 248
		BGSEquipIndex equipIndex;						 // 250
		float distanceMoved;							 // 254
		float movementDelta;							 // 258
		float scale;									 // 25C
		std::uint64_t flags;							 // 260
		bool artRequested;								 // 268
		bool animationsLoaded;							 // 269
	};
	static_assert(sizeof(Projectile) == 0x270);

	class __declspec(novtable) MissileProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MissileProjectile };
		inline static constexpr auto VTABLE{ VTABLE::MissileProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPMIS };

		// add
		virtual bool ShouldReorient() const; // EA

		// members
		NiMatrix3 dismemberedLimbRotation;					 // 270
		NiPoint3 dismemberedLimbOffset;						 // 2A0
		NiPointer<bhkNPCollisionObject> modelCollision;		 // 2B0
		REX::Enum<ImpactResult, std::uint32_t> impactResult; // 2B8
		bool waitingToInitialize3D;							 // 2BC
		bool deferProcessImpale;							 // 2BD
	};
	static_assert(sizeof(MissileProjectile) == 0x2C0);

	class __declspec(novtable) ArrowProjectile
		: public MissileProjectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ArrowProjectile };
		inline static constexpr auto VTABLE{ VTABLE::ArrowProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPARW };

		// members
		AlchemyItem* poison; // 2C0
	};
	static_assert(sizeof(ArrowProjectile) == 0x2D0);

	class __declspec(novtable) GrenadeProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GrenadeProjectile };
		inline static constexpr auto VTABLE{ VTABLE::GrenadeProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPGRE };

		// members
		BGSDecalGroup* decalGroup; // 270
		bool collisionGroupReset;  // 278
	};
	static_assert(sizeof(GrenadeProjectile) == 0x280);

	class ProjectileLaunchData
	{
	public:
		// members
		NiPoint3 origin;							  // 00
		NiPoint3 contactNormal;						  // 0C
		BGSProjectile* projectileBase;				  // 18
		TESObjectREFR* shooter;						  // 20
		CombatController* shooterCombatController;	  // 28
		BGSObjectInstanceT<TESObjectWEAP> fromWeapon; // 30
		TESAmmo* fromAmmo;							  // 40
		BGSEquipIndex equipIndex;					  // 48
		float zAngle;								  // 4C
		float xAngle;								  // 50
		float yAngle;								  // 54
		TESObjectREFR* homingTarget;				  // 58
		TESObjectCELL* parentCell;					  // 60
		MagicItem* spell;							  // 68
		MagicSystem::CastingSource castingSource;	  // 70
		AlchemyItem* poison;						  // 78
		std::int32_t area;							  // 80
		float power;								  // 84
		float scale;								  // 88
		float coneOfFireRadiusMult;					  // 8C
		BGSBodyPartDefs::LIMB_ENUM targetLimb;		  // 90
		bool alwaysHit;								  // 94
		bool noDamageOutsideCombat;					  // 95
		bool autoAim;								  // 96
		bool useOrigin;								  // 97
		bool deferInitialization;					  // 98
		bool tracer;								  // 99
		bool forceConeOfFire;						  // 9A
		bool intentionalMiss;						  // 9B
		bool allow3D;								  // 9C
		bool penetrates;							  // 9D
		bool ignoreNearCollisions;					  // 9E
	};
	static_assert(sizeof(ProjectileLaunchData) == 0xA0);

	class __declspec(novtable) BeamProjectile
		: public Projectile,								// 000
		  public BSTEventSource<BeamProjectileImpactEvent>, // 278
		  public BSTEventSink<BSProceduralGeomEvent>		// 270
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BeamProjectile };
		inline static constexpr auto VTABLE{ VTABLE::BeamProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPBEA };

		// members
		ProjectileLaunchData launchData;		  // 2D0
		bhkCollisionQueryResultHandle castResult; // 370
		float baseModelLength;					  // 378
		bool transformSet;						  // 37C
		bool queueUncull;						  // 37D
		bool dealtDamage;						  // 37E
	};
	static_assert(sizeof(BeamProjectile) == 0x380);

	class __declspec(novtable) FlameProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FlameProjectile };
		inline static constexpr auto VTABLE{ VTABLE::FlameProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPFLA };

		// members
		float expirationTimer; // 270
		float coneAngle;	   // 274
	};
	static_assert(sizeof(FlameProjectile) == 0x280);

	class __declspec(novtable) ConeProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ConeProjectile };
		inline static constexpr auto VTABLE{ VTABLE::ConeProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPCON };

		// members
		float expirationTimer; // 270
		float coneAngle;	   // 274
	};
	static_assert(sizeof(ConeProjectile) == 0x280);

	class __declspec(novtable) BarrierProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BarrierProjectile };
		inline static constexpr auto VTABLE{ VTABLE::BarrierProjectile };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPBAR };

		struct CollisionData
		{
		public:
			// members
			ObjectRefHandle ref; // 00
			std::uint32_t count; // 04
		};
		static_assert(sizeof(CollisionData) == 0x8);

		// members
		float width;						   // 270
		BSTArray<CollisionData> collisionData; // 278
	};
	static_assert(sizeof(BarrierProjectile) == 0x290);
}

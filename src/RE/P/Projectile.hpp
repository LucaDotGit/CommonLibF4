#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/bhkCollisionQueryResultHandle.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
}

namespace RE::CELLJobs
{
	class AnimatedRefJobData;
}

namespace RE::MagicSystem
{
	enum class CastingSource : std::int32_t;
}

namespace RE
{
	enum class COL_LAYER : std::int32_t;
	enum class ImpactResult : std::int32_t;

	class bhkNPCollisionObject;
	class BSMagicShaderParticles;
	class hknpAllHitsCollector;
	class hknpShape;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class QueuedFile;

	class __declspec(novtable) Projectile : public TESObjectREFR // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Projectile;
		inline static constexpr const auto& VTABLE = VTABLE::Projectile;
		inline static constexpr auto FORM_TYPE = FormType::ObjectReference;

		class ImpactCreation;

		class ImpactData
		{
		public:
			// members
			NiPoint3 location;												// 0x00
			NiPoint3 normal;												// 0x0C
			bhkCollisionQueryResultHandle impactDecalQuery;					// 0x18
			ObjectRefHandle collidee;										// 0x20
			NiPointer<bhkNPCollisionObject> colObj;							// 0x28
			BGSMaterialType* materialType;									// 0x30
			REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> damageLimb; // 0x38
			REX::Enum<COL_LAYER, std::int32_t> collisionLayer;				// 0x3C
			NiPointer<NiNode> closestBone;									// 0x40
			REX::Enum<ImpactResult, std::int32_t> resultOverride;			// 0x48
			REX::Float32 decalSize;											// 0x4C
			std::uint32_t collisionShapeKey;								// 0x50
			std::int16_t targetWorldObjectCount;							// 0x54
			std::int16_t targetWorldObjectIndex;							// 0x56
			bool processed;													// 0x58
			bool spellCast;													// 0x59
			bool effectSpawned;												// 0x5A
			bool backface;													// 0x5B
		};

		static_assert(sizeof(ImpactData) == 0x60);

		// add
		virtual auto IsMissileProjectile() const -> bool;			 // 0xC6 - { return false; }
		virtual auto IsGrenadeProjectile() const -> bool;			 // 0xC7 - { return false; }
		virtual auto IsFlameProjectile() const -> bool;				 // 0xC8 - { return false; }
		virtual auto IsBeamProjectile() const -> bool;				 // 0xC9 - { return false; }
		virtual auto IsFogProjectile() const -> bool;				 // 0xCA - { return false; }
		virtual auto IsBarrierProjectile() const -> bool;			 // 0xCB - { return false; }
		virtual void OnKill();										 // 0xCC - { return; }
		virtual void Process3D();									 // 0xCD - { return; }
		virtual void PostLoad3D(NiAVObject* a_obj3D);				 // 0xCE
		virtual void UpdateImpl(REX::Float32 a_deltaTime) = 0;		 // 0xCF
		virtual auto ProcessImpacts() -> bool;						 // 0xD0
		virtual void Update3D(CELLJobs::AnimatedRefJobData* a_data); // 0xD1
		virtual auto IsMine() const -> bool;						 // 0xD2 - { return false; }
		virtual auto GetPowerSpeedMult() const
			-> REX::Float32; // 0xD3 - { return spell ? static_cast<REX::Float32>(1.0) : power; }
		virtual auto GetWeaponSpeedMult() const -> REX::Float32; // 0xD4 - { return static_cast<REX::Float32>(1.0); }
		virtual auto GetStopMainSoundAfterImpact() -> bool;		 // 0xD5 - { return false; }
		virtual void ReportHavokDeactivation();					 // 0xD6 - { return; }
		virtual auto TurnOff(Actor* a_actionActor, bool a_silent) -> bool;	   // 0xD7
		virtual auto IsPermanent() -> bool;									   // 0xD8
		virtual auto GetGravity() const -> REX::Float32;					   // 0xD9
		virtual void CleanUpPointersOnDisable();							   // 0xDA
		virtual auto RunTargetPick() -> bool;								   // 0xDB
		virtual auto GetKillOnCollision() const -> bool;					   // 0xDC - { return true; }
		virtual auto ShouldBeLimited() const -> bool;						   // 0xDD - { return false; }
		virtual auto TargetsWholeBody() const -> bool;						   // 0xDE - { return false; }
		virtual auto GetAllowMovement() const -> bool;						   // 0xDF
		virtual auto GetCollisionGroup() const -> std::uint32_t;			   // 0xE0
		virtual auto GetCollisionShape() -> hknpShape*;						   // 0xE1
		virtual void InitializeImpl();										   // 0xE2 - { return; }
		virtual void Relaunch();											   // 0xE3 - { return; }
		virtual auto AddImpact(const ImpactCreation& a_data) -> std::uint32_t; // 0xE4
		virtual auto HandleHits(
			const hknpAllHitsCollector& a_collector,
			const NiPoint3& a_from,
			const NiPoint3& a_to) -> bool;			   // 0xE5
		virtual void OnEnterTrigger();				   // 0xE6 - { return; }
		virtual void AddInitialVelocity();			   // 0xE7
		virtual void Handle3DLoaded();				   // 0xE8 - { return; }
		virtual auto ShouldUseDesiredTarget() -> bool; // 0xE9 - { return false; }

		// members
		BSTArray<ImpactData> impacts;									   // 0x110
		NiTransform followOffset;										   // 0x130
		NiPointer<bhkNPCollisionObject> collisionObject;				   // 0x170
		NiPointer<TESObjectREFR> droppedRefr;							   // 0x178
		NiPoint3 movementDirection;										   // 0x180
		NiPoint3 velocity;												   // 0x18C
		NiPointer<NiLight> light;										   // 0x198
		NiPointer<ActorCause> actorCause;								   // 0x1A0
		ObjectRefHandle shooter;										   // 0x1A8
		ObjectRefHandle desiredTarget;									   // 0x1AC
		BSSoundHandle sndHandle;										   // 0x1B0
		BSSoundHandle sndCountdown;										   // 0x1B8
		BGSExplosion* explosion;										   // 0x1C0
		MagicItem* spell;												   // 0x1C8
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 0x1D0
		EffectSetting* avEffect;										   // 0x1D8
		NiPointer<QueuedFile> projectileDBFiles;						   // 0x1E0
		void* muzzleFlashDBHandle; // 0x1E8 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
								   // BSResource::EntryDBTraits<BSModelDB::DBTraits,
								   // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>,
								   // BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> muzzleFlashArt;								// 0x1F0
		BSMagicShaderParticles* particles;								// 0x1F8
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb; // 0x200
		NiPointer<NiAVObject> targetLimbObj;							// 0x208
		NiAVObject* clonePoolKey;										// 0x210
		REX::Float32 power;												// 0x218
		REX::Float32 speedMult;											// 0x21C
		REX::Float32 range;												// 0x220
		REX::Float32 age;												// 0x224
		REX::Float32 damage;											// 0x228
		REX::Float32 alpha;												// 0x22C
		REX::Float32 explosionTimer;									// 0x230
		REX::Float32 blinkTimer;										// 0x234
		BGSObjectInstanceT<TESObjectWEAP> weaponSource;					// 0x238
		TESAmmo* ammoSource;											// 0x248
		BGSEquipIndex equipIndex;										// 0x250
		REX::Float32 distanceMoved;										// 0x254
		REX::Float32 movementDelta;										// 0x258
		REX::Float32 scale;												// 0x25C
		std::uint64_t flags;											// 0x260
		bool artRequested;												// 0x268
		bool animationsLoaded;											// 0x269
	};

	static_assert(sizeof(Projectile) == 0x270);
}

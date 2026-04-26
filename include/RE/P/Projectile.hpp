#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/bhkCollisionQueryResultHandle.hpp"
#include "RE/C/CELLJobs.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
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

	class __declspec(novtable) Projectile
		: public TESObjectREFR // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Projectile };
		inline static constexpr auto VTABLE{ VTABLE::Projectile };
		inline static constexpr auto FORM_TYPE{ FormType::kObjectReference };

		class ImpactCreation;

		class ImpactData
		{
		public:
			// members
			NiPoint3 location;												// 00
			NiPoint3 normal;												// 0C
			bhkCollisionQueryResultHandle impactDecalQuery;					// 18
			ObjectRefHandle collidee;										// 20
			NiPointer<bhkNPCollisionObject> colObj;							// 28
			BGSMaterialType* materialType;									// 30
			REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> damageLimb; // 38
			REX::Enum<COL_LAYER, std::int32_t> collisionLayer;				// 3C
			NiPointer<NiNode> closestBone;									// 40
			REX::Enum<ImpactResult, std::int32_t> resultOverride;			// 48
			REX::Float32 decalSize;											// 4C
			std::uint32_t collisionShapeKey;								// 50
			std::int16_t targetWorldObjectCount;							// 54
			std::int16_t targetWorldObjectIndex;							// 56
			bool processed;													// 58
			bool spellCast;													// 59
			bool effectSpawned;												// 5A
			bool backface;													// 5B
		};
		static_assert(sizeof(ImpactData) == 0x60);

		// add
		virtual bool IsMissileProjectile() const;																		// C6 - { return false; }
		virtual bool IsGrenadeProjectile() const;																		// C7 - { return false; }
		virtual bool IsFlameProjectile() const;																			// C8 - { return false; }
		virtual bool IsBeamProjectile() const;																			// C9 - { return false; }
		virtual bool IsFogProjectile() const;																			// CA - { return false; }
		virtual bool IsBarrierProjectile() const;																		// CB - { return false; }
		virtual void OnKill();																							// CC - { return; }
		virtual void Process3D();																						// CD - { return; }
		virtual void PostLoad3D(NiAVObject* a_obj3D);																	// CE
		virtual void UpdateImpl(REX::Float32 a_delta) = 0;																// CF
		virtual bool ProcessImpacts();																					// D0
		virtual void Update3D(CELLJobs::AnimatedRefJobData* a_data);													// D1
		virtual bool IsMine() const;																					// D2 - { return false; }
		virtual REX::Float32 GetPowerSpeedMult() const;																	// D3 - { return spell ? 1.0_f32 : power; }
		virtual REX::Float32 GetWeaponSpeedMult() const;																// D4 - { return 1.0_f32; }
		virtual bool GetStopMainSoundAfterImpact();																		// D5 - { return false; }
		virtual void ReportHavokDeactivation();																			// D6 - { return; }
		virtual bool TurnOff(Actor* a_actionActor, bool a_silent);														// D7
		virtual bool IsPermanent();																						// D8
		virtual REX::Float32 GetGravity() const;																		// D9
		virtual void CleanUpPointersOnDisable();																		// DA
		virtual bool RunTargetPick();																					// DB
		virtual bool GetKillOnCollision() const;																		// DC - { return true; }
		virtual bool ShouldBeLimited() const;																			// DD - { return false; }
		virtual bool TargetsWholeBody() const;																			// DE - { return false; }
		virtual bool GetAllowMovement() const;																			// DF
		virtual std::uint32_t GetCollisionGroup() const;																// E0
		virtual hknpShape* GetCollisionShape();																			// E1
		virtual void InitializeImpl();																					// E2 - { return; }
		virtual void Relaunch();																						// E3 - { return; }
		virtual std::uint32_t AddImpact(const ImpactCreation& a_data);													// E4
		virtual bool HandleHits(const hknpAllHitsCollector& a_collector, const NiPoint3& a_from, const NiPoint3& a_to); // E5
		virtual void OnEnterTrigger();																					// E6 - { return; }
		virtual void AddInitialVelocity();																				// E7
		virtual void Handle3DLoaded();																					// E8 - { return; }
		virtual bool ShouldUseDesiredTarget();																			// E9 - { return false; }

		// members
		BSTArray<ImpactData> impacts;									   // 110
		NiTransform followOffset;										   // 130
		NiPointer<bhkNPCollisionObject> collisionObject;				   // 170
		NiPointer<TESObjectREFR> droppedRefr;							   // 178
		NiPoint3 movementDirection;										   // 180
		NiPoint3 velocity;												   // 18C
		NiPointer<NiLight> light;										   // 198
		NiPointer<ActorCause> actorCause;								   // 1A0
		ObjectRefHandle shooter;										   // 1A8
		ObjectRefHandle desiredTarget;									   // 1AC
		BSSoundHandle sndHandle;										   // 1B0
		BSSoundHandle sndCountdown;										   // 1B8
		BGSExplosion* explosion;										   // 1C0
		MagicItem* spell;												   // 1C8
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 1D0
		EffectSetting* avEffect;										   // 1D8
		NiPointer<QueuedFile> projectileDBFiles;						   // 1E0
		void* muzzleFlashDBHandle;										   // 1E8 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> muzzleFlashArt;								   // 1F0
		BSMagicShaderParticles* particles;								   // 1F8
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb;	   // 200
		NiPointer<NiAVObject> targetLimbObj;							   // 208
		NiAVObject* clonePoolKey;										   // 210
		REX::Float32 power;												   // 218
		REX::Float32 speedMult;											   // 21C
		REX::Float32 range;												   // 220
		REX::Float32 age;												   // 224
		REX::Float32 damage;											   // 228
		REX::Float32 alpha;												   // 22C
		REX::Float32 explosionTimer;									   // 230
		REX::Float32 blinkTimer;										   // 234
		BGSObjectInstanceT<TESObjectWEAP> weaponSource;					   // 238
		TESAmmo* ammoSource;											   // 248
		BGSEquipIndex equipIndex;										   // 250
		REX::Float32 distanceMoved;										   // 254
		REX::Float32 movementDelta;										   // 258
		REX::Float32 scale;												   // 25C
		std::uint64_t flags;											   // 260
		bool artRequested;												   // 268
		bool animationsLoaded;											   // 269
	};
	static_assert(sizeof(Projectile) == 0x270);
}

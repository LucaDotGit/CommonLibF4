#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/H/hknpClosestUniqueBodyIdHitCollector.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
}

namespace RE
{
	class ActorCause;
	class NiLight;
	class NonActorMagicCaster;

	class __declspec(novtable) Explosion
		: public TESObjectREFR // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Explosion };
		inline static constexpr auto VTABLE{ VTABLE::Explosion };
		inline static constexpr auto FORM_TYPE{ FormType::kObjectReference };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kDecalsPlaced = 1 << 0,
			kTargetsFound = 1 << 1,
			kTargetsProcessed = 1 << 2,
			kForcesApplied = 1 << 3,
			kIgnoreIsSwap = 1 << 4,
			kUnderwater = 1 << 5,
			kInitialized = 1 << 6,
			kNonHostile = 1 << 7,
			kWaterTestDone = 1 << 8,
			kSoundTestDone = 1 << 9
		};

		class ExplodedLimb
		{
		public:
			// members
			REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limb; // 00
			ActorValueInfo* limbCondition;							  // 08
			REX::Float32 distance;									  // 10
		};
		static_assert(sizeof(ExplodedLimb) == 0x18);

		class ExplosionTarget
		{
		public:
			enum class Flags : std::uint32_t
			{
				kNone = 0,
				kHitWeakPoint = 1 << 0,
				kMobile = 1 << 1,
				kProcessed = 1 << 2,
				kProcessedLimbs = 1 << 3
			};

			// members
			ObjectRefHandle ref;					  // 00
			REX::EnumSet<Flags, std::uint32_t> flags; // 04
			REX::Float32 hitFromExplosionSqrLen;	  // 08
			BSTArray<ExplodedLimb> limbArray;		  // 10
		};
		static_assert(sizeof(ExplosionTarget) == 0x28);

		// add
		virtual void Initialize();				   // C6
		virtual void Update(REX::Float32 a_delta); // C7
		virtual void FindTargets();				   // C8

		// members
		hknpClosestUniqueBodyIdHitCollector collector;	// 110
		void* explosionDBHandle;						// 520 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		REX::Float32 age;								// 528
		REX::Float32 obj3DLifetime;						// 52C
		REX::Float32 audioLifetime;						// 530
		REX::Float32 buildTime;							// 534
		REX::Float32 innerRadius;						// 538
		REX::Float32 outerRadius;						// 53C
		REX::Float32 imageSpaceRadius;					// 540
		REX::Float32 damageMult;						// 544
		BSSimpleList<ExplosionTarget*> targetList;		// 548
		BSTSmallArray<BSSoundHandle, 4> soundHandles;	// 558
		NiPointer<NiLight> light;						// 588
		ObjectRefHandle owner;							// 590
		ObjectRefHandle explodedRef;					// 594
		ObjectRefHandle createdRef;						// 598
		BSTSmartPointer<ActorCause> actorCause;			// 5A0
		NonActorMagicCaster* caster;					// 5A8
		BGSObjectInstanceT<TESObjectWEAP> weaponSource; // 5B0
		std::int32_t frameCount;						// 5C0
		NiPoint3A closestPoint;							// 5D0
		NiPoint3A closestPointNormal;					// 5E0
		REX::Float32 calculatedDamage;					// 5F0
		REX::Float32 scale;								// 5F4
		REX::EnumSet<Flags, std::uint32_t> flags;		// 5F8
	};
	static_assert(sizeof(Explosion) == 0x600);
}

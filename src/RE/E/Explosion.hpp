#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/H/hknpClosestUniqueBodyIdHitCollector.hpp"
#include "RE/N/NiPoint3.hpp"
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

	class __declspec(novtable) Explosion : public TESObjectREFR // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Explosion;
		inline static constexpr const auto& VTABLE = VTABLE::Explosion;
		inline static constexpr auto FORM_TYPE = FormType::ObjectReference;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			DecalsPlaced = 1 << 0,
			TargetsFound = 1 << 1,
			TargetsProcessed = 1 << 2,
			ForcesApplied = 1 << 3,
			IgnoreIsSwap = 1 << 4,
			Underwater = 1 << 5,
			Initialized = 1 << 6,
			NonHostile = 1 << 7,
			WaterTestDone = 1 << 8,
			SoundTestDone = 1 << 9
		};

		class ExplodedLimb
		{
		public:
			// members
			REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limb; // 0x00
			ActorValueInfo* limbCondition;							  // 0x08
			REX::Float32 distance;									  // 0x10
		};

		static_assert(sizeof(ExplodedLimb) == 0x18);

		class ExplosionTarget
		{
		public:
			enum class Flags : std::uint32_t
			{
				None = 0,
				HitWeakPoint = 1 << 0,
				Mobile = 1 << 1,
				Processed = 1 << 2,
				ProcessedLimbs = 1 << 3
			};

			// members
			ObjectRefHandle ref;					  // 0x00
			REX::EnumSet<Flags, std::uint32_t> flags; // 0x04
			REX::Float32 hitFromExplosionSqrLen;	  // 0x08
			BSTArray<ExplodedLimb> limbArray;		  // 0x10
		};

		static_assert(sizeof(ExplosionTarget) == 0x28);

		// add
		virtual void Initialize();					   // 0xC6
		virtual void Update(REX::Float32 a_deltaTime); // 0xC7
		virtual void FindTargets();					   // 0xC8

		auto GetDamage() const -> REX::Float32
		{
			using FuncType = decltype(&Explosion::GetDamage);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Explosion::GetDamage);
			return std::invoke(FUNC, this);
		}

		void ProcessTargets()
		{
			using FuncType = decltype(&Explosion::ProcessTargets);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Explosion::ProcessTargets);
			std::invoke(FUNC, this);
		}

		// members
		hknpClosestUniqueBodyIdHitCollector collector; // 0x110
		void* explosionDBHandle;	   // 0x520 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
									   // BSResource::EntryDBTraits<BSModelDB::DBTraits,
									   // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>,
									   // BSResource::EntryDB<BSModelDB::DBTraits>>`
		REX::Float32 age;			   // 0x528
		REX::Float32 obj3DLifetime;	   // 0x52C
		REX::Float32 audioLifetime;	   // 0x530
		REX::Float32 buildTime;		   // 0x534
		REX::Float32 innerRadius;	   // 0x538
		REX::Float32 outerRadius;	   // 0x53C
		REX::Float32 imageSpaceRadius; // 0x540
		REX::Float32 damageMult;	   // 0x544
		BSSimpleList<ExplosionTarget*> targetList;		// 0x548
		BSTSmallArray<BSSoundHandle, 4> soundHandles;	// 0x558
		NiPointer<NiLight> light;						// 0x588
		ObjectRefHandle owner;							// 0x590
		ObjectRefHandle explodedRef;					// 0x594
		ObjectRefHandle createdRef;						// 0x598
		BSTSmartPointer<ActorCause> actorCause;			// 0x5A0
		NonActorMagicCaster* caster;					// 0x5A8
		BGSObjectInstanceT<TESObjectWEAP> weaponSource; // 0x5B0
		std::int32_t frameCount;						// 0x5C0
		NiPoint3A closestPoint;							// 0x5D0
		NiPoint3A closestPointNormal;					// 0x5E0
		REX::Float32 calculatedDamage;					// 0x5F0
		REX::Float32 scale;								// 0x5F4
		REX::EnumSet<Flags, std::uint32_t> flags;		// 0x5F8
	};

	static_assert(sizeof(Explosion) == 0x600);
}

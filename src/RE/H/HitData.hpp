#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/D/DamageImpactData.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
}

namespace RE
{
	enum class STAGGER_MAGNITUDE : std::int32_t;

	class BGSAttackData;
	class VATSCommand;

	class HitData
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			Blocked = 1 << 0,
			BlockWithWeapon = 1 << 1,
			BlockCandidate = 1 << 2,
			Critical = 1 << 3,
			CriticalOnDeath = 1 << 4,
			Fatal = 1 << 5,
			DismemberLimb = 1 << 6,
			ExplodeLimb = 1 << 7,
			CrippleLimb = 1 << 8,
			Disarm = 1 << 9,
			DisableWeapon = 1 << 10,
			SneakAttack = 1 << 11,
			IgnoreCritical = 1 << 12,
			PredictDamage = 1 << 13,
			PredictBaseDamage = 1 << 14,
			Bash = 1 << 15,
			TimedBash = 1 << 16,
			PowerAttack = 1 << 17,
			MeleeAttack = 1 << 18,
			Ricochet = 1 << 19,
			Explosion = 1 << 20
		};

		void CollectDamage(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, REX::Float32 a_mult)
		{
			using FuncType = decltype(&HitData::CollectDamage);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HitData::CollectDamage);
			std::invoke(FUNC, this, a_weapon, a_mult);
		}

		// members
		DamageImpactData impactData;												// 0x00
		ActorHandle aggressor;														// 0x40
		ActorHandle target;															// 0x44
		ObjectRefHandle sourceRef;													// 0x48
		NiPointer<BGSAttackData> attackData;										// 0x50
		BGSObjectInstanceT<TESObjectWEAP> weapon;									// 0x58
		SpellItem* criticalEffect;													// 0x68
		SpellItem* hitEffect;														// 0x70
		BSTSmartPointer<VATSCommand> vatsCommand;									// 0x78
		TESAmmo* ammo;																// 0x80
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 0x88
		REX::Float32 healthDamage;													// 0x90
		REX::Float32 totalDamage;													// 0x94
		REX::Float32 physicalDamage;												// 0x98
		REX::Float32 targetedLimbDamage;											// 0x9C
		REX::Float32 percentBlocked;												// 0xA0
		REX::Float32 resistedPhysicalDamage;										// 0xA4
		REX::Float32 resistedTypedDamage;											// 0xA8
		REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerMagnitude;				// 0xAC
		REX::Float32 sneakAttackBonus;												// 0xB0
		REX::Float32 bonusHealthDamageMult;											// 0xB4
		REX::Float32 pushBack;														// 0xB8
		REX::Float32 reflectedDamage;												// 0xBC
		REX::Float32 criticalDamageMult;											// 0xC0
		REX::EnumSet<Flags, std::uint32_t> flags;									// 0xC4
		BGSEquipIndex equipIndex;													// 0xC8
		std::uint32_t materialID;													// 0xCC
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> damageLimb;				// 0xD0
	};

	static_assert(sizeof(HitData) == 0xE0);
}

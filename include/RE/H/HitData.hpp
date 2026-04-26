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
			kNone = 0,
			kBlocked = 1 << 0,
			kBlockWithWeapon = 1 << 1,
			kBlockCandidate = 1 << 2,
			kCritical = 1 << 3,
			kCriticalOnDeath = 1 << 4,
			kFatal = 1 << 5,
			kDismemberLimb = 1 << 6,
			kExplodeLimb = 1 << 7,
			kCrippleLimb = 1 << 8,
			kDisarm = 1 << 9,
			kDisableWeapon = 1 << 10,
			kSneakAttack = 1 << 11,
			kIgnoreCritical = 1 << 12,
			kPredictDamage = 1 << 13,
			kPredictBaseDamage = 1 << 14,
			kBash = 1 << 15,
			kTimedBash = 1 << 16,
			kPowerAttack = 1 << 17,
			kMeleeAttack = 1 << 18,
			kRicochet = 1 << 19,
			kExplosion = 1 << 20
		};

		// members
		DamageImpactData impactData;												// 00
		ActorHandle aggressor;														// 40
		ActorHandle target;															// 44
		ObjectRefHandle sourceRef;													// 48
		NiPointer<BGSAttackData> attackData;										// 50
		BGSObjectInstanceT<TESObjectWEAP> weapon;									// 58
		SpellItem* criticalEffect;													// 68
		SpellItem* hitEffect;														// 70
		BSTSmartPointer<VATSCommand> vatsCommand;									// 78
		TESAmmo* ammo;																// 80
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 88
		REX::Float32 healthDamage;													// 90
		REX::Float32 totalDamage;													// 94
		REX::Float32 physicalDamage;												// 98
		REX::Float32 targetedLimbDamage;											// 9C
		REX::Float32 percentBlocked;												// A0
		REX::Float32 resistedPhysicalDamage;										// A4
		REX::Float32 resistedTypedDamage;											// A8
		REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerMagnitude;				// AC
		REX::Float32 sneakAttackBonus;												// B0
		REX::Float32 bonusHealthDamageMult;											// B4
		REX::Float32 pushBack;														// B8
		REX::Float32 reflectedDamage;												// BC
		REX::Float32 criticalDamageMult;											// C0
		REX::EnumSet<Flags, std::uint32_t> flags;									// C4
		BGSEquipIndex equipIndex;													// C8
		std::uint32_t materialID;													// D0
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> damageLimb;				// D4
	};
	static_assert(sizeof(HitData) == 0xE0);
}

#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/N/NiPoint3.hpp"

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
	class CombatController;

	class ProjectileLaunchData
	{
	public:
		// members
		NiPoint3 origin;												   // 0x00
		NiPoint3 contactNormal;											   // 0x0C
		BGSProjectile* projectileBase;									   // 0x18
		TESObjectREFR* shooter;											   // 0x20
		CombatController* shooterCombatController;						   // 0x28
		BGSObjectInstanceT<TESObjectWEAP> fromWeapon;					   // 0x30
		TESAmmo* fromAmmo;												   // 0x40
		BGSEquipIndex equipIndex;										   // 0x48
		REX::Float32 zAngle;											   // 0x4C
		REX::Float32 xAngle;											   // 0x50
		REX::Float32 yAngle;											   // 0x54
		TESObjectREFR* homingTarget;									   // 0x58
		TESObjectCELL* parentCell;										   // 0x60
		MagicItem* spell;												   // 0x68
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 0x70
		AlchemyItem* poison;											   // 0x78
		std::int32_t area;												   // 0x80
		REX::Float32 power;												   // 0x84
		REX::Float32 scale;												   // 0x88
		REX::Float32 coneOfFireRadiusMult;								   // 0x8C
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb;	   // 0x90
		bool alwaysHit;													   // 0x94
		bool noDamageOutsideCombat;										   // 0x95
		bool autoAim;													   // 0x96
		bool useOrigin;													   // 0x97
		bool deferInitialization;										   // 0x98
		bool tracer;													   // 0x99
		bool forceConeOfFire;											   // 0x9A
		bool intentionalMiss;											   // 0x9B
		bool allow3D;													   // 0x9C
		bool penetrates;												   // 0x9D
		bool ignoreNearCollisions;										   // 0x9E
	};

	static_assert(sizeof(ProjectileLaunchData) == 0xA0);
}

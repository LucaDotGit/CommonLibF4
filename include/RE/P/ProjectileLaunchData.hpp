#pragma once

#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/N/NiPoint.hpp"

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
		NiPoint3 origin;												   // 00
		NiPoint3 contactNormal;											   // 0C
		BGSProjectile* projectileBase;									   // 18
		TESObjectREFR* shooter;											   // 20
		CombatController* shooterCombatController;						   // 28
		BGSObjectInstanceT<TESObjectWEAP> fromWeapon;					   // 30
		TESAmmo* fromAmmo;												   // 40
		BGSEquipIndex equipIndex;										   // 48
		REX::Float32 zAngle;											   // 4C
		REX::Float32 xAngle;											   // 50
		REX::Float32 yAngle;											   // 54
		TESObjectREFR* homingTarget;									   // 58
		TESObjectCELL* parentCell;										   // 60
		MagicItem* spell;												   // 68
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 70
		AlchemyItem* poison;											   // 78
		std::int32_t area;												   // 80
		REX::Float32 power;												   // 84
		REX::Float32 scale;												   // 88
		REX::Float32 coneOfFireRadiusMult;								   // 8C
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb;	   // 90
		bool alwaysHit;													   // 94
		bool noDamageOutsideCombat;										   // 95
		bool autoAim;													   // 96
		bool useOrigin;													   // 97
		bool deferInitialization;										   // 98
		bool tracer;													   // 99
		bool forceConeOfFire;											   // 9A
		bool intentionalMiss;											   // 9B
		bool allow3D;													   // 9C
		bool penetrates;												   // 9D
		bool ignoreNearCollisions;										   // 9E
	};
	static_assert(sizeof(ProjectileLaunchData) == 0xA0);
}

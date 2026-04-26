#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;
	enum class STAGGER_MAGNITUDE : std::int32_t;

	class BGSExplosionData
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kAlwaysUsesWorldOrientation = 1 << 1,
			kKnockDown_Always = 1 << 2,
			kKnockDown_ByFormula = 1 << 3,
			kIgnoreLOSCheck = 1 << 4,
			kPushExplosionSourceRefOnly = 1 << 5,
			kIgnoreImageSpaceSwap = 1 << 6,
			kChain = 1 << 7,
			kNoControllerVibration = 1 << 8,
			kPlacedObjectPersists = 1 << 9,
			kSkipUnderwaterTest = 1 << 10
		};

		// members
		TESObjectLIGH* light;										 // 00
		BGSSoundDescriptorForm* sound01;							 // 08
		BGSSoundDescriptorForm* sound02;							 // 10
		BGSImpactDataSet* impactDataSet;							 // 18
		TESBoundObject* impactPlacedObject;							 // 20
		BGSProjectile* spawnProjectile;								 // 28
		NiPoint3 projectileVector;									 // 30
		REX::Float32 projectileSpread;								 // 3C
		std::uint32_t projectileCount;								 // 40
		REX::Float32 force;											 // 44
		REX::Float32 damage;										 // 48
		REX::Float32 innerRadius;									 // 4C
		REX::Float32 outerRadius;									 // 50
		REX::Float32 imageSpaceRadius;								 // 54
		REX::Float32 verticalOffsetMult;							 // 58
		REX::EnumSet<Flags, std::uint32_t> flags;					 // 5C
		REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel;			 // 60
		REX::Float32 placedObjectFadeDelay;							 // 64
		REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerMagnitude; // 68
	};
	static_assert(sizeof(BGSExplosionData) == 0x70);
}

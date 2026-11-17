#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;
	enum class STAGGER_MAGNITUDE : std::int32_t;

	class BGSExplosionData
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			AlwaysUsesWorldOrientation = 1 << 1,
			KnockDown_Always = 1 << 2,
			KnockDown_ByFormula = 1 << 3,
			IgnoreLOSCheck = 1 << 4,
			PushExplosionSourceRefOnly = 1 << 5,
			IgnoreImageSpaceSwap = 1 << 6,
			Chain = 1 << 7,
			NoControllerVibration = 1 << 8,
			PlacedObjectPersists = 1 << 9,
			SkipUnderwaterTest = 1 << 10
		};

		// members
		TESObjectLIGH* light;										 // 0x00
		BGSSoundDescriptorForm* sound01;							 // 0x08
		BGSSoundDescriptorForm* sound02;							 // 0x10
		BGSImpactDataSet* impactDataSet;							 // 0x18
		TESBoundObject* impactPlacedObject;							 // 0x20
		BGSProjectile* spawnProjectile;								 // 0x28
		NiPoint3 projectileVector;									 // 0x30
		REX::Float32 projectileSpread;								 // 0x3C
		std::uint32_t projectileCount;								 // 0x40
		REX::Float32 force;											 // 0x44
		REX::Float32 damage;										 // 0x48
		REX::Float32 innerRadius;									 // 0x4C
		REX::Float32 outerRadius;									 // 0x50
		REX::Float32 imageSpaceRadius;								 // 0x54
		REX::Float32 verticalOffsetMult;							 // 0x58
		REX::EnumSet<Flags, std::uint32_t> flags;					 // 0x5C
		REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel;			 // 0x60
		REX::Float32 placedObjectFadeDelay;							 // 0x64
		REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerMagnitude; // 0x68
	};

	static_assert(sizeof(BGSExplosionData) == 0x70);
}

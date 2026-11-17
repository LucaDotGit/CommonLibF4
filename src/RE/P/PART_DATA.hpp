#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class PART_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			Severable = 1 << 0,
			IKData = 1 << 1,
			IKData_BipedData = 1 << 2,
			Explodable = 1 << 3,
			IKData_IsHead = 1 << 4,
			IKData_HeadTracking = 1 << 5,
			ToHitChance_Absolute = 1 << 6
		};

		// members
		REX::Float32 damageMult;				   // 0x00
		BGSDebris* explosionGenericDebris;		   // 0x08
		BGSExplosion* explosion;				   // 0x10
		REX::Float32 explosionGenericDebrisScale;  // 0x18
		BGSDebris* dismemberGenericDebris;		   // 0x20
		BGSExplosion* dismemberExplosion;		   // 0x28
		REX::Float32 dismemberGenericDebrisScale;  // 0x30
		BGSDebris* onCrippleGenericDebris;		   // 0x38
		BGSExplosion* onCrippleExplosion;		   // 0x40
		REX::Float32 onCrippleGenericDebrisScale;  // 0x48
		NiPoint3 goreTranslate;					   // 0x4C
		NiPoint3 goreRotate;					   // 0x58
		BGSImpactDataSet* dismemberImpactDataSet;  // 0x68
		BGSImpactDataSet* explosionImpactDataSet;  // 0x70
		BGSImpactDataSet* onCrippleImpactDataSet;  // 0x78
		ActorValueInfo* actorValue;				   // 0x80
		BGSArtObject* artObject;				   // 0x88
		REX::Float32 explosionSpecialDebrisScale;  // 0x90
		REX::EnumSet<Flags, std::uint8_t> flags;   // 0x94
		std::uint8_t type;						   // 0x95
		std::uint8_t healthPercent;				   // 0x96
		std::uint8_t toHitChance;				   // 0x97
		std::uint8_t explosionChance;			   // 0x98
		std::uint8_t nonLethalDismembermentChance; // 0x99
		std::uint8_t dismemberGenericDebrisCount;  // 0x9A
		std::uint8_t onCrippleGenericDebrisCount;  // 0x9B
		std::uint8_t explosionGenericDebrisCount;  // 0x9C
		std::uint8_t dismemberDecalCount;		   // 0x9D
		std::uint8_t onCrippleDecalCount;		   // 0x9E
		std::uint8_t explosionDecalCount;		   // 0x9F
		std::uint8_t geometrySegmentIndex;		   // 0xA0
	};

	static_assert(sizeof(PART_DATA) == 0xA8);
}

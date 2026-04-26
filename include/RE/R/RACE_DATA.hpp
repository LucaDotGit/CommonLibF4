#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	enum class BIPED_OBJECT : std::int32_t;
	enum class RACE_SIZE : std::int32_t;

	class RACE_DATA
	{
	public:
		// members
		std::array<REX::Float32, 2> height;					// 000
		std::array<NiPoint3, 2> weight;						// 008
		std::int32_t flags;									// 020
		REX::Float32 accelerate;							// 024
		REX::Float32 decelerate;							// 028
		REX::Enum<RACE_SIZE, std::int32_t> raceSize;		// 02C
		REX::Enum<BIPED_OBJECT, std::int32_t> headObject;	// 030
		REX::Enum<BIPED_OBJECT, std::int32_t> hairObject;	// 034
		REX::Enum<BIPED_OBJECT, std::int32_t> beardObject;	// 038
		REX::Float32 injuredHealthPercent;					// 03C
		REX::Enum<BIPED_OBJECT, std::int32_t> shieldObject; // 040
		REX::Enum<BIPED_OBJECT, std::int32_t> bodyObject;	// 044
		REX::Float32 aimAngleTolerance;						// 048
		REX::Float32 flightRadius;							// 04C
		REX::Float32 angleAccelerate;						// 050
		REX::Float32 angleTolerance;						// 054
		std::uint32_t flags02;								// 058
		NiPoint3 mountOffset;								// 05C
		NiPoint3 dismountOffset;							// 068
		NiPoint3 mountCameraOffset;							// 074
		REX::Enum<BIPED_OBJECT, std::int32_t> pipboyObject; // 080
		std::int16_t xpValue;								// 084
		BGSExplosion* onCrippleExplosion;					// 088
		BGSDebris* onCrippleGenericDebris;					// 090
		BGSImpactDataSet* onCrippleImpactDataSet;			// 098
		REX::Float32 onCrippleGenericDebrisScale;			// 0A0
		std::int8_t onCrippleGenericDebrisCount;			// 0A4
		std::int8_t onCrippleDecalCount;					// 0A5
		BGSExplosion* dismemberExplosion;					// 0A8
		BGSDebris* dismemberGenericDebris;					// 0B0
		BGSImpactDataSet* dismemberImpactDataSet;			// 0B8
		REX::Float32 dismemberGenericDebrisScale;			// 0C0
		std::int8_t dismemberGenericDebrisCount;			// 0C4
		std::int8_t dismemberDecalCount;					// 0C5
		BGSExplosion* explosion;							// 0C8
		BGSDebris* explosionGenericDebris;					// 0D0
		BGSImpactDataSet* explosionImpactDataSet;			// 0D8
		REX::Float32 explosionGenericDebrisScale;			// 0E0
		std::int8_t explosionGenericDebrisCount;			// 0E4
		std::int8_t explosionDecalCount;					// 0E5
		BGSExplosion* subsegmentExplosion;					// 0E8
		REX::Float32 maxPitch;								// 0F0
		REX::Float32 maxRoll;								// 0F4
		REX::Float32 defaultHeadHeight;						// 0F8
	};
	static_assert(sizeof(RACE_DATA) == 0x100);
}

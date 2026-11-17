#pragma once

#include "RE/N/NiPoint3.hpp"
#include "RE/S/SEX.hpp"

namespace RE
{
	enum class BIPED_OBJECT : std::int32_t;
	enum class RACE_SIZE : std::int32_t;

	class RACE_DATA
	{
	public:
		// members
		std::array<REX::Float32, std::to_underlying(SEX::_Count)> height; // 0x00
		std::array<NiPoint3, std::to_underlying(SEX::_Count)> weight;	  // 0x08
		std::int32_t flags;												  // 0x020
		REX::Float32 accelerate;										  // 0x024
		REX::Float32 decelerate;										  // 0x028
		REX::Enum<RACE_SIZE, std::int32_t> raceSize;					  // 0x02C
		REX::Enum<BIPED_OBJECT, std::int32_t> headObject;				  // 0x030
		REX::Enum<BIPED_OBJECT, std::int32_t> hairObject;				  // 0x034
		REX::Enum<BIPED_OBJECT, std::int32_t> beardObject;				  // 0x038
		REX::Float32 injuredHealthPercent;								  // 0x03C
		REX::Enum<BIPED_OBJECT, std::int32_t> shieldObject;				  // 0x040
		REX::Enum<BIPED_OBJECT, std::int32_t> bodyObject;				  // 0x044
		REX::Float32 aimAngleTolerance;									  // 0x048
		REX::Float32 flightRadius;										  // 0x04C
		REX::Float32 angleAccelerate;									  // 0x050
		REX::Float32 angleTolerance;									  // 0x054
		std::uint32_t flags02;											  // 0x058
		NiPoint3 mountOffset;											  // 0x05C
		NiPoint3 dismountOffset;										  // 0x068
		NiPoint3 mountCameraOffset;										  // 0x074
		REX::Enum<BIPED_OBJECT, std::int32_t> pipboyObject;				  // 0x080
		std::int16_t xpValue;											  // 0x084
		BGSExplosion* onCrippleExplosion;								  // 0x088
		BGSDebris* onCrippleGenericDebris;								  // 0x090
		BGSImpactDataSet* onCrippleImpactDataSet;						  // 0x098
		REX::Float32 onCrippleGenericDebrisScale;						  // 0x0A0
		std::int8_t onCrippleGenericDebrisCount;						  // 0x0A4
		std::int8_t onCrippleDecalCount;								  // 0x0A5
		BGSExplosion* dismemberExplosion;								  // 0x0A8
		BGSDebris* dismemberGenericDebris;								  // 0x0B0
		BGSImpactDataSet* dismemberImpactDataSet;						  // 0x0B8
		REX::Float32 dismemberGenericDebrisScale;						  // 0x0C0
		std::int8_t dismemberGenericDebrisCount;						  // 0x0C4
		std::int8_t dismemberDecalCount;								  // 0x0C5
		BGSExplosion* explosion;										  // 0x0C8
		BGSDebris* explosionGenericDebris;								  // 0x0D0
		BGSImpactDataSet* explosionImpactDataSet;						  // 0x0D8
		REX::Float32 explosionGenericDebrisScale;						  // 0x0E0
		std::int8_t explosionGenericDebrisCount;						  // 0x0E4
		std::int8_t explosionDecalCount;								  // 0x0E5
		BGSExplosion* subsegmentExplosion;								  // 0x0E8
		REX::Float32 maxPitch;											  // 0x0F0
		REX::Float32 maxRoll;											  // 0x0F4
		REX::Float32 defaultHeadHeight;									  // 0x0F8
	};

	static_assert(sizeof(RACE_DATA) == 0x100);
}

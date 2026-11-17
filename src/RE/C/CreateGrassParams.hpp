#pragma once

#include "RE/T/TESGrass.hpp"

namespace RE
{
	class GrassParam;
	class NiPoint3;

	class CreateGrassParams
	{
	public:
		// members
		std::int32_t cellX;						// 0x00
		std::int32_t cellY;						// 0x04
		std::int32_t block;						// 0x08
		TESObjectLAND* land;					// 0x10
		NiPoint3* coord;						// 0x18
		GrassParam* grassParam;					// 0x20
		REX::Float32* density;					// 0x28
		REX::Float32 heightLimit;				// 0x30
		TESGrass::GRASS_WATER_STATE waterState; // 0x34
		REX::Float32 cellWaterHeight;			// 0x38
		std::uint32_t minSlope;					// 0x3C
		std::uint32_t maxSlope;					// 0x40
		std::uint32_t randomSeed;				// 0x44
	};

	static_assert(sizeof(CreateGrassParams) == 0x48);
}

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
		std::int32_t cellX;						// 00
		std::int32_t cellY;						// 04
		std::int32_t block;						// 08
		TESObjectLAND* land;					// 10
		NiPoint3* coord;						// 18
		GrassParam* grassParam;					// 20
		REX::Float32* density;					// 28
		REX::Float32 heightLimit;				// 30
		TESGrass::GRASS_WATER_STATE waterState; // 34
		REX::Float32 cellWaterHeight;			// 38
		std::uint32_t minSlope;					// 3C
		std::uint32_t maxSlope;					// 40
		std::uint32_t randomSeed;				// 44
	};
	static_assert(sizeof(CreateGrassParams) == 0x48);
}

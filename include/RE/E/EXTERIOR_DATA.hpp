#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSTerrainVisibilityData;

	class EXTERIOR_DATA
	{
	public:
		GAME_HEAP_REDEFINE_NEW(EXTERIOR_DATA)

		enum class LandHideFlags : std::uint8_t
		{
			kNone = 0,
			kQuad1 = 1 << 0,
			kQuad2 = 1 << 1,
			kQuad3 = 1 << 2,
			kQuad4 = 1 << 3
		};

		// members
		std::int32_t cellX;										 // 00
		std::int32_t cellY;										 // 04
		std::uint8_t* maxHeightData;							 // 08
		BGSTerrainVisibilityData* lodVisibilityData;			 // 10
		REX::Float32 maxHeight;									 // 18
		REX::Float32 worldX;									 // 1C
		REX::Float32 worldY;									 // 20
		REX::EnumSet<LandHideFlags, std::uint8_t> landHideFlags; // 24
	};
	static_assert(sizeof(EXTERIOR_DATA) == 0x28);
}

#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSTerrainVisibilityData;

	class EXTERIOR_DATA
	{
	public:
		GAME_HEAP_REDEFINE_NEW(EXTERIOR_DATA);

		enum class LandHideFlags : std::uint8_t
		{
			None = 0,
			Quad1 = 1 << 0,
			Quad2 = 1 << 1,
			Quad3 = 1 << 2,
			Quad4 = 1 << 3
		};

		// members
		std::int32_t cellX;										 // 0x00
		std::int32_t cellY;										 // 0x04
		std::uint8_t* maxHeightData;							 // 0x08
		BGSTerrainVisibilityData* lodVisibilityData;			 // 0x10
		REX::Float32 maxHeight;									 // 0x18
		REX::Float32 worldX;									 // 0x1C
		REX::Float32 worldY;									 // 0x20
		REX::EnumSet<LandHideFlags, std::uint8_t> landHideFlags; // 0x24
	};

	static_assert(sizeof(EXTERIOR_DATA) == 0x28);
}

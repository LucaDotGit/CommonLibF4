#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::PowerUtils
{
	class GridConnection;
	class GridSaveLoadData;

	class PowerGrid
	{
	public:
		// members
		BSTHashMap<std::uint32_t, BSTSet<GridConnection>*> adjacencyMap; // 00 - maps powered objects to the objects they connect to
		BSTArray<GridSaveLoadData> loadGameDataArray;					 // 30
		std::uint32_t loadElement;										 // 48
		BSTArray<std::uint32_t> currentlyPowered;						 // 50
		REX::Float32 capacity;											 // 68
		REX::Float32 load;												 // 6C
	};
	static_assert(sizeof(PowerGrid) == 0x70);
}

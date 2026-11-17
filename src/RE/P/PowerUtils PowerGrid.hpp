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
		BSTHashMap<std::uint32_t, BSTSet<GridConnection>*>
			adjacencyMap;							  // 0x00 - maps powered objects to the objects they connect to
		BSTArray<GridSaveLoadData> loadGameDataArray; // 0x30
		std::uint32_t loadElement;					  // 0x48
		BSTArray<std::uint32_t> currentlyPowered;	  // 0x50
		REX::Float32 capacity;						  // 0x68
		REX::Float32 load;							  // 0x6C
	};

	static_assert(sizeof(PowerGrid) == 0x70);
}

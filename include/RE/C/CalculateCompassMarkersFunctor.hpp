#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTObjectArena.hpp"

namespace RE
{
	class HUDMarkerData;

	class CalculateCompassMarkersFunctor
	{
	public:
		// members
		BSTHeapObjectArena<HUDMarkerData, 48> hudMarkerDataArray; // 00
		BSTArray<std::uint32_t> compassLocationIndices;			  // 30
		std::uint32_t locationUpdateIndex;						  // 50
	};
	static_assert(sizeof(CalculateCompassMarkersFunctor) == 0x58);
}

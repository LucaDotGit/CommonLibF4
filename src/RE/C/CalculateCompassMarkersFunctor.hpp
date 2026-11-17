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
		BSTHeapObjectArena<HUDMarkerData, 0x30> hudMarkerDataArray; // 0x00
		BSTArray<std::uint32_t> compassLocationIndices;				// 0x30
		std::uint32_t locationUpdateIndex;							// 0x50
	};

	static_assert(sizeof(CalculateCompassMarkersFunctor) == 0x58);
}

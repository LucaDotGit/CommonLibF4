#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSNavmeshGrid
	{
	public:
		// members
		std::uint32_t gridSize;			   // 00
		REX::Float32 columnSectionLen;	   // 04
		REX::Float32 rowSectionLen;		   // 08
		NiPoint3 gridBoundsMin;			   // 0C
		NiPoint3 gridBoundsMax;			   // 18
		BSTArray<std::uint16_t>* gridData; // 28
	};
	static_assert(sizeof(BSNavmeshGrid) == 0x30);
}

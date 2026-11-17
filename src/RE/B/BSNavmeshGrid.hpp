#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSNavmeshGrid
	{
	public:
		// members
		std::uint32_t gridSize;			   // 0x00
		REX::Float32 columnSectionLen;	   // 0x04
		REX::Float32 rowSectionLen;		   // 0x08
		NiPoint3 gridBoundsMin;			   // 0x0C
		NiPoint3 gridBoundsMax;			   // 0x18
		BSTArray<std::uint16_t>* gridData; // 0x28
	};

	static_assert(sizeof(BSNavmeshGrid) == 0x30);
}

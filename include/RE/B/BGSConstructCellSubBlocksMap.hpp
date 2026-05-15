#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellsMap;

	class BGSConstructCellSubBlocksMap
		: public BSTHashMap<std::uint32_t, BGSConstructCellsMap*> // 00
	{
		// members
	};
	static_assert(sizeof(BGSConstructCellSubBlocksMap) == 0x30);
}

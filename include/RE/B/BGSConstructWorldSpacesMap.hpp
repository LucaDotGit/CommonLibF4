#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellBlocksMap;

	class BGSConstructWorldSpacesMap
		: public BSTHashMap<std::uint32_t, BGSConstructCellBlocksMap*> // 00
	{
		// members
	};
	static_assert(sizeof(BGSConstructWorldSpacesMap) == 0x30);
}

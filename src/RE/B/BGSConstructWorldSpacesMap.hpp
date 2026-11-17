#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellBlocksMap;

	class BGSConstructWorldSpacesMap : public BSTHashMap<std::uint32_t, BGSConstructCellBlocksMap*> // 0x00
	{
		// members
	};

	static_assert(sizeof(BGSConstructWorldSpacesMap) == 0x30);
}

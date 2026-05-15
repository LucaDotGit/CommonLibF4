#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellSubBlocksMap;
	class BGSConstructFormsMap;

	class BGSConstructCellBlocksMap
		: public BSTHashMap<std::uint32_t, BGSConstructCellSubBlocksMap*> // 00
	{
	public:
		// members
		BGSConstructFormsMap* persistentCell; // 00
		bool bExteriors;					  // 08
	};
	static_assert(sizeof(BGSConstructCellBlocksMap) == 0x40);
}

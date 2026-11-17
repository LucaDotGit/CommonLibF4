#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellSubBlocksMap;
	class BGSConstructFormsMap;

	class BGSConstructCellBlocksMap : public BSTHashMap<std::uint32_t, BGSConstructCellSubBlocksMap*> // 0x00
	{
	public:
		// members
		BGSConstructFormsMap* persistentCell; // 0x00
		bool bExteriors;					  // 0x08
	};

	static_assert(sizeof(BGSConstructCellBlocksMap) == 0x40);
}

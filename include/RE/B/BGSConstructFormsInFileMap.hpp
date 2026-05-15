#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellBlocksMap;
	class BGSConstructFormsMap;
	class BGSConstructWorldSpacesMap;

	class BGSConstructFormsInFileMap
		: public BSTHashMap<std::uint32_t, BGSConstructFormsMap*> // 00
	{
	public:
		// members
		BGSConstructCellBlocksMap* interiorCells; // 30
		BGSConstructWorldSpacesMap* worldSpaces;  // 38
		std::uint32_t count;					  // 40
	};
	static_assert(sizeof(BGSConstructFormsInFileMap) == 0x48);
}

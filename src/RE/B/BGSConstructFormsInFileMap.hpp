#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructCellBlocksMap;
	class BGSConstructFormsMap;
	class BGSConstructWorldSpacesMap;

	class BGSConstructFormsInFileMap : public BSTHashMap<std::uint32_t, BGSConstructFormsMap*> // 0x00
	{
	public:
		// members
		BGSConstructCellBlocksMap* interiorCells; // 0x30
		BGSConstructWorldSpacesMap* worldSpaces;  // 0x38
		std::uint32_t count;					  // 0x40
	};

	static_assert(sizeof(BGSConstructFormsInFileMap) == 0x48);
}

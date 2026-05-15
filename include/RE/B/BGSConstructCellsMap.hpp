#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructFormsMap;

	class BGSConstructCellsMap
		: public BSTHashMap<std::uint32_t, BGSConstructFormsMap*> // 00
	{
		// members
	};
	static_assert(sizeof(BGSConstructCellsMap) == 0x30);
}

#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSSaveLoadFormIDMap
	{
	public:
		// members
		BSTHashMap<TESFormID, std::uint32_t> formIDToIndexMap; // 0x00
		BSTHashMap<std::uint32_t, TESFormID> indexToFormIDMap; // 0x30
		std::uint32_t currentIndex;							   // 0x60
	};

	static_assert(sizeof(BGSSaveLoadFormIDMap) == 0x68);
}

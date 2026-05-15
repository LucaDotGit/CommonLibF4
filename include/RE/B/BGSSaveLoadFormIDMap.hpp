#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSSaveLoadFormIDMap
	{
	public:
		// members
		BSTHashMap<TESFormID, std::uint32_t> formIDToIndexMap; // 00
		BSTHashMap<std::uint32_t, TESFormID> indexToFormIDMap; // 30
		std::uint32_t currentIndex;							   // 60
	};
	static_assert(sizeof(BGSSaveLoadFormIDMap) == 0x68);
}

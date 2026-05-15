#pragma once

#include "RE/B/BGSCellNumericIDArrayMap.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSSaveLoadReferencesMap
	{
	public:
		// members
		BSTHashMap<std::uint32_t, std::uint32_t> movedReferencesMap;				  // 00
		BGSCellNumericIDArrayMap interiorReferencesMap;								  // 30
		BSTHashMap<std::uint32_t, BGSCellNumericIDArrayMap*> worldspaceReferencesMap; // 60
		mutable BSSpinLock lock;													  // 90
	};
	static_assert(sizeof(BGSSaveLoadReferencesMap) == 0x98);
}

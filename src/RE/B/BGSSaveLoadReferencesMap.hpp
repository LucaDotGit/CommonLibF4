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
		BSTHashMap<std::uint32_t, std::uint32_t> movedReferencesMap;				  // 0x00
		BGSCellNumericIDArrayMap interiorReferencesMap;								  // 0x30
		BSTHashMap<std::uint32_t, BGSCellNumericIDArrayMap*> worldspaceReferencesMap; // 0x60
		mutable BSSpinLock lock;													  // 0x90
	};

	static_assert(sizeof(BGSSaveLoadReferencesMap) == 0x98);
}

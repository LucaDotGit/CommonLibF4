#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/U/UnloadedRefData.hpp"

namespace RE
{
	class OverrideData
	{
	public:
		GAME_HEAP_REDEFINE_NEW(OverrideData);

		// members
		BSTArray<UnloadedRefData> addedDataArray; // 0x00
		BSTSet<TESFormID> removedDataSet;		  // 0x18
	};

	static_assert(sizeof(OverrideData) == 0x48);
}

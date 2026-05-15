#pragma once

#include "RE/B/BGSFormChanges.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSSaveLoadChangesMap
		: public BSTHashMap<TESFormID, BGSFormChanges> // 00
	{
	public:
		// members
		mutable BSReadWriteLock rwLock; // 30
	};
	static_assert(sizeof(BGSSaveLoadChangesMap) == 0x38);
}

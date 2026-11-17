#pragma once

#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiExtraData;

	class NiExtraDataContainer
	{
	public:
		GAME_HEAP_REDEFINE_NEW(NiExtraDataContainer);

		// members
		BSTArray<NiPointer<NiExtraData>> dataArray; // 0x00
		mutable BSReadWriteLock lock;				// 0x18
	};

	static_assert(sizeof(NiExtraDataContainer) == 0x20);
}

#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiExtraData;

	class NiExtraDataContainer
	{
	public:
		// members
		BSTArray<NiPointer<NiExtraData>> dataArray; // 00
		mutable BSReadWriteLock lock;				// 18
	};
	static_assert(sizeof(NiExtraDataContainer) == 0x20);
}

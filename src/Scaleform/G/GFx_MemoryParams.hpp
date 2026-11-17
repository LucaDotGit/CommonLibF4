#pragma once

#include "Scaleform/M/MemoryHeap.hpp"

namespace Scaleform::GFx
{
	class MemoryParams
	{
	public:
		// members
		MemoryHeap::HeapDesc desc;												// 0x00
		REX::Float32 heapLimitMultiplier{static_cast<REX::Float32>(0.25)};		// 0x40
		std::uint32_t maxCollectionRoots{static_cast<std::uint32_t>(-1)};		// 0x44
		std::uint32_t framesBetweenCollections{static_cast<std::uint32_t>(-1)}; // 0x48
		std::uint32_t initialDynamicLimit{static_cast<std::uint32_t>(-1)};		// 0x4C
		std::uint32_t runsToUpgradeGen{static_cast<std::uint32_t>(-1)};			// 0x50
		std::uint32_t runsToCollectYoung{static_cast<std::uint32_t>(-1)};		// 0x54
		std::uint32_t runsToCollectOld{static_cast<std::uint32_t>(-1)};			// 0x58
	};

	static_assert(sizeof(MemoryParams) == 0x60);
}

#pragma once

#include "Scaleform/M/MemoryHeap.hpp"

namespace Scaleform::GFx
{
	class MemoryParams
	{
	public:
		// members
		MemoryHeap::HeapDesc desc;												  // 00
		REX::Float32 heapLimitMultiplier{ 0.25_f32 };							  // 40
		std::uint32_t maxCollectionRoots{ static_cast<std::uint32_t>(-1) };		  // 44
		std::uint32_t framesBetweenCollections{ static_cast<std::uint32_t>(-1) }; // 48
		std::uint32_t initialDynamicLimit{ static_cast<std::uint32_t>(-1) };	  // 4C
		std::uint32_t runsToUpgradeGen{ static_cast<std::uint32_t>(-1) };		  // 50
		std::uint32_t runsToCollectYoung{ static_cast<std::uint32_t>(-1) };		  // 54
		std::uint32_t runsToCollectOld{ static_cast<std::uint32_t>(-1) };		  // 58
	};
	static_assert(sizeof(MemoryParams) == 0x60);
}

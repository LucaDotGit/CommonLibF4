#pragma once

#include "RE/B/BGSLoadGameSubBuffer.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSSaveLoadQueuedSubBufferMap
	{
	public:
		// members
		std::array<BSTHashMap<TESForm*, BGSLoadGameSubBuffer>, 3> QueuedSubBuffers; // 00
	};
	static_assert(sizeof(BGSSaveLoadQueuedSubBufferMap) == 0x90);
}

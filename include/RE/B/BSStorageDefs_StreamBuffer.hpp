#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BSStorageDefs
{
	class StreamBuffer
	{
	public:
		GAME_HEAP_REDEFINE_NEW(StreamBuffer);

		// members
		std::size_t size;					   // 00
		MemoryManager::AutoScrapBuffer buffer; // 08
		std::byte* ptrCur;					   // 10
	};
	static_assert(sizeof(StreamBuffer) == 0x18);
}

#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BSStorageDefs
{
	class StreamBuffer
	{
	public:
		GAME_HEAP_REDEFINE_NEW(StreamBuffer);

		// members
		std::size_t size;					   // 0x00
		MemoryManager::AutoScrapBuffer buffer; // 0x08
		std::byte* ptrCur;					   // 0x10
	};

	static_assert(sizeof(StreamBuffer) == 0x18);
}

#pragma once

namespace RE::BSSmallBlockAllocatorUtil
{
	class BlockPage;

	class Pool
	{
	public:
		// members
		BlockPage* pageList;				// 0x00
		BlockPage* currAlloc;				// 0x08
		std::uint32_t totalFreeBlocks;		// 0x10
		std::uint32_t totalAllocatedBlocks; // 0x14
		std::uint32_t totalBytes;			// 0x18
		std::uint32_t elementSize;			// 0x1C
	};

	static_assert(sizeof(Pool) == 0x20);
}

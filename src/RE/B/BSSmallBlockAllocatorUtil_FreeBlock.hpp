#pragma once

namespace RE::BSSmallBlockAllocatorUtil
{
	class FreeBlock
	{
	public:
		// members
		FreeBlock* next; // 0x00
	};

	static_assert(sizeof(FreeBlock) == 0x08);
}

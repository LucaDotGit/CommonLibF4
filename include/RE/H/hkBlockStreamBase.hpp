#pragma once

#include "RE/H/hkInplaceArray.hpp"

namespace RE
{
	class hkBlockStreamAllocator;

	class hkBlockStreamBase
	{
	public:
		class Stream;

		class Block
		{
		public:
			// members
			std::uint32_t numElementsAndBytesUsed; // 00
			std::int32_t blockIndexInStream;	   // 04
			Block* next;						   // 08
			hkBlockStreamAllocator* allocator;	   // 10
			Stream* blockStream;				   // 18
			std::array<std::byte, 0xFE0> data;	   // 20
		};
		static_assert(sizeof(Block) == 0x1000);

		class Stream
		{
		public:
			// members
			hkBlockStreamAllocator* allocator;			// 00
			std::int32_t numTotalElements;				// 08
			Stream* blockStreamPPU;						// 10
			bool partiallyFreed;						// 18
			bool zeroNewBlocks;							// 19
			bool isLocked;								// 1A
			bool spuWronglySentConsumedBlockStreamBack; // 1B
			hkInplaceArrayAligned16<Block*, 24> blocks; // 20
		};
		static_assert(sizeof(Stream) == 0x100);
	};
	static_assert(std::is_empty_v<hkBlockStreamBase>);
}

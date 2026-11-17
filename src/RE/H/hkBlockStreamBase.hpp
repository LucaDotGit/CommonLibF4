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
			std::uint32_t numElementsAndBytesUsed; // 0x00
			std::int32_t blockIndexInStream;	   // 0x04
			Block* next;						   // 0x08
			hkBlockStreamAllocator* allocator;	   // 0x10
			Stream* blockStream;				   // 0x18
			std::array<std::byte, 0xFE0> data;	   // 0x20
		};

		static_assert(sizeof(Block) == 0x1000);

		class Stream
		{
		public:
			// members
			hkBlockStreamAllocator* allocator;			// 0x00
			std::int32_t numTotalElements;				// 0x08
			Stream* blockStreamPPU;						// 0x10
			bool partiallyFreed;						// 0x18
			bool zeroNewBlocks;							// 0x19
			bool isLocked;								// 0x1A
			bool spuWronglySentConsumedBlockStreamBack; // 0x1B
			hkInplaceArrayAligned16<Block*, 24> blocks; // 0x20
		};

		static_assert(sizeof(Stream) == 0x100);
	};

	static_assert(std::is_empty_v<hkBlockStreamBase>);
}

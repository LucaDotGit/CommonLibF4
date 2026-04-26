#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_ID.hpp"

namespace RE::BSTextureStreamer
{
	class LocalHeap
	{
	public:
		class Block
		{
		public:
			// members
			std::size_t sizeFlags; // 00
			Block* prev;		   // 08
		};
		static_assert(sizeof(Block) == 0x10);

		class FreeBlock
			: public Block
		{
		public:
			// members
			FreeBlock* left;			// 00
			FreeBlock* right;			// 08
			FreeBlock** root;			// 10
			FreeBlock* leftSibling;		// 18
			FreeBlock* rightSibling;	// 20
			std::size_t parentAndBlack; // 28
		};
		static_assert(sizeof(FreeBlock) == 0x40);

		class FreeBlockAccess
		{
		public:
		};
		static_assert(std::is_empty_v<FreeBlockAccess>);

		// members
		std::byte* memoryBase;		   // 00
		FreeBlock* freeList;		   // 08
		std::uint32_t freeBlocks;	   // 10
		std::uint32_t allocatedBlocks; // 14
	};
	static_assert(sizeof(LocalHeap) == 0x18);

	class ChunkDesc
	{
	public:
		// members
		std::uint64_t dataFileOffset;	// 00
		std::uint32_t size;				// 08
		std::uint32_t uncompressedSize; // 0C
		std::uint16_t mipFirst;			// 10
		std::uint16_t mipLast;			// 12
		std::uint32_t padding;			// 14
	};
	static_assert(sizeof(ChunkDesc) == 0x18);

	class TextureDescHeader
	{
	public:
		// members
		BSResource::ID id;				 // 00
		std::uint8_t dataFileIndex{ 0 }; // 0C
		std::uint8_t chunkCount{ 0 };	 // 0D
		std::uint16_t chunkOffset{ 0 };	 // 0E
	};
	static_assert(sizeof(TextureDescHeader) == 0x10);

	template <class T>
	class NativeDesc
		: public TextureDescHeader // 00
	{
	public:
		// members
		T info{};						   // 10
		std::array<ChunkDesc, 4> chunks{}; // ??
		BSFixedString streamName;		   // ??
	};
}

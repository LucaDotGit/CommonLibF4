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
			std::size_t sizeFlags; // 0x00
			Block* prev;		   // 0x08
		};

		static_assert(sizeof(Block) == 0x10);

		class FreeBlock : public Block
		{
		public:
			// members
			FreeBlock* left;			// 0x00
			FreeBlock* right;			// 0x08
			FreeBlock** root;			// 0x10
			FreeBlock* leftSibling;		// 0x18
			FreeBlock* rightSibling;	// 0x20
			std::size_t parentAndBlack; // 0x28
		};

		static_assert(sizeof(FreeBlock) == 0x40);

		class FreeBlockAccess
		{
		public:
		};

		static_assert(std::is_empty_v<FreeBlockAccess>);

		// members
		std::byte* memoryBase;		   // 0x00
		FreeBlock* freeList;		   // 0x08
		std::uint32_t freeBlocks;	   // 0x10
		std::uint32_t allocatedBlocks; // 0x14
	};

	static_assert(sizeof(LocalHeap) == 0x18);

	class ChunkDesc
	{
	public:
		// members
		std::uint64_t dataFileOffset;	// 0x00
		std::uint32_t size;				// 0x08
		std::uint32_t uncompressedSize; // 0x0C
		std::uint16_t mipFirst;			// 0x10
		std::uint16_t mipLast;			// 0x12
		std::uint32_t padding;			// 0x14
	};

	static_assert(sizeof(ChunkDesc) == 0x18);

	class TextureDescHeader
	{
	public:
		// members
		BSResource::ID id;			   // 0x00
		std::uint8_t dataFileIndex{0}; // 0x0C
		std::uint8_t chunkCount{0};	   // 0x0D
		std::uint16_t chunkOffset{0};  // 0x0E
	};

	static_assert(sizeof(TextureDescHeader) == 0x10);

	template <class T>
	class NativeDesc : public TextureDescHeader // 0x00
	{
	public:
		// members
		T info{};						   // 0x10
		std::array<ChunkDesc, 4> chunks{}; // 0x??
		BSFixedString streamName;		   // 0x??
	};
}

#pragma once

#include "RE/B/BSCriticalSection.hpp"
#include "RE/B/BSSmallBlockAllocatorUtil_Pool.hpp"
#include "RE/I/IMemoryStore.hpp"

namespace RE::BSSmallBlockAllocatorUtil
{
	class FreeBlock;
}

namespace RE
{
	class __declspec(novtable) BSSmallBlockAllocator : IMemoryStore // 0x0000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSSmallBlockAllocator;
		inline static constexpr const auto& VTABLE = VTABLE::BSSmallBlockAllocator;

		class BlockPageInternal
		{
		public:
			// members
			BlockPageInternal* left;					  // 0x00
			BlockPageInternal* right;					  // 0x08
			BSSmallBlockAllocatorUtil::FreeBlock* blocks; // 0x10
			std::uint16_t totalElements;				  // 0x18
			std::uint16_t freeElements;					  // 0x1A
			std::uint16_t elementSize;					  // 0x1C
			std::uint16_t check;						  // 0x1E
		};

		static_assert(sizeof(BlockPageInternal) == 0x20);

		class MegaBlockPage
		{
		public:
			// members
			std::array<std::byte, 0x1F'E000> mem;				  // 0x000000
			std::array<BlockPageInternal, 0xFF> blockPages;		  // 0x1FE000
			BSSmallBlockAllocator::MegaBlockPage* left;			  // 0x1FFFE0
			BSSmallBlockAllocator::MegaBlockPage* right;		  // 0x1FFFE8
			BSSmallBlockAllocatorUtil::BlockPage* freeBlockPages; // 0x1FFFF0
			std::uint16_t numFreeBlockPages;					  // 0x1FFFF8
			std::uint16_t nextBlockPageAlloc;					  // 0x1FFFFA
			bool decommitted;									  // 0x1FFFFC
		};

		static_assert(sizeof(MegaBlockPage) == 0x20'0000);

		class Pool : BSSmallBlockAllocatorUtil::Pool // 0x00
		{
		public:
			// members
			BSCriticalSection lock; // 0x20
		};

		static_assert(sizeof(Pool) == 0x48);

		~BSSmallBlockAllocator() override; // 0x00

		// members
		std::array<BSSmallBlockAllocator::Pool, 64> pools;		  // 0x0008
		BSCriticalSection lock;									  // 0x1208
		std::uint16_t addressSpaceSize;							  // 0x1230
		std::byte* allocBase;									  // 0x1238
		std::byte* blockPageCommitMin;							  // 0x1240
		std::byte* blockPageCommit;								  // 0x1248
		BSSmallBlockAllocator::MegaBlockPage* megaBlockPageList;  // 0x1250
		BSSmallBlockAllocator::MegaBlockPage* megaBlockCurrAlloc; // 0x1258
		std::uint32_t totalFreeBlockPages;						  // 0x1260
		bool allowDecommits;									  // 0x1264
	};

	static_assert(sizeof(BSSmallBlockAllocator) == 0x1268);
}

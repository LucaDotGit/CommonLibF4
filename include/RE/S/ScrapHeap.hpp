#pragma once

#include "RE/I/IMemoryStore.hpp"

namespace RE
{
	class __declspec(novtable) ScrapHeap
		: public IMemoryStore // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ScrapHeap };
		inline static constexpr auto VTABLE{ VTABLE::ScrapHeap };

		class Block
		{
		public:
			// members
			std::size_t sizeFlags; // 00
			Block* prev;		   // 08
		};
		static_assert(sizeof(Block) == 0x10);

		class FreeBlock
			: public Block // 00
		{
		public:
			// members
			FreeBlock* left;  // 10
			FreeBlock* right; // 18
		};
		static_assert(sizeof(FreeBlock) == 0x20);

		class FreeTreeNode
			: public FreeBlock // 00
		{
		public:
			// members
			FreeTreeNode** root;		// 20
			FreeTreeNode* leftNode;		// 28
			FreeTreeNode* rightNode;	// 30
			std::size_t parentAndBlack; // 38
		};
		static_assert(sizeof(FreeTreeNode) == 0x40);

		~ScrapHeap() override; // 00 - { REX::W32::VirtualFree(baseAddress, 0, REX::W32::MEM_RELEASE); }

		// override (IMemoryStore)
		std::size_t Size(const void* a_mem) const override;								 // 01 - { return *static_cast<const std::size_t*>(a_mem) & ~(static_cast<std::size_t>(3) << 62); }
		void GetMemoryStats(MemoryStats* a_stats) override;								 // 02 - { return; }
		bool ContainsBlockImpl(const void* a_block) const override;						 // 03 - { return baseAddress <= a_block && a_block <= endAddress; }
		void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) override; // 04 - { return Allocate(a_size, a_alignment); }
		void DeallocateAlignImpl(void*& a_block) override;								 // 05 - { Deallocate(a_block), a_block = nullptr; }

		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* Allocate(std::size_t a_size, std::align_val_t a_alignment);
		__declspec(noalias) void Deallocate(void* a_mem);

		// members
		std::array<FreeBlock*, 6> smallBlocks{ nullptr }; // 08
		FreeTreeNode* freeList{ nullptr };				  // 38
		Block* lastBlock{ nullptr };					  // 40
		std::byte* baseAddress{ nullptr };				  // 48
		std::byte* endAddress{ nullptr };				  // 50
		std::byte* commitEnd{ nullptr };				  // 58
		std::size_t reserveSize;						  // 60
		std::size_t minCommit{ 1 << 17 };				  // 68
		std::size_t totalAllocated{ 0 };				  // 70
		std::uint32_t keepPagesRequest{ 0 };			  // 78
		std::uint32_t totalFreeBlocks{ 0 };				  // 7C
		std::uint32_t freeSmallBlocks{ 0 };				  // 80
		std::uint32_t totalAllocatedBlocks{ 0 };		  // 84
		std::uint32_t pmpBarrier{ 0 };					  // 88
	};
	static_assert(sizeof(ScrapHeap) == 0x90);
}

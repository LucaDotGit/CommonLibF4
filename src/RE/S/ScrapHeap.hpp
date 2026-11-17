#pragma once

#include "RE/I/IMemoryStore.hpp"

namespace RE
{
	class __declspec(novtable) ScrapHeap : public IMemoryStore // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ScrapHeap;
		inline static constexpr const auto& VTABLE = VTABLE::ScrapHeap;

		class Block
		{
		public:
			// members
			std::size_t sizeFlags; // 0x00
			Block* prev;		   // 0x08
		};

		static_assert(sizeof(Block) == 0x10);

		class FreeBlock : public Block // 0x00
		{
		public:
			// members
			FreeBlock* left;  // 0x10
			FreeBlock* right; // 0x18
		};

		static_assert(sizeof(FreeBlock) == 0x20);

		class FreeTreeNode : public FreeBlock // 0x00
		{
		public:
			// members
			FreeTreeNode** root;		// 0x20
			FreeTreeNode* leftNode;		// 0x28
			FreeTreeNode* rightNode;	// 0x30
			std::size_t parentAndBlack; // 0x38
		};

		static_assert(sizeof(FreeTreeNode) == 0x40);

		~ScrapHeap() override; // 0x00 - { REX::W32::VirtualFree(baseAddress, 0, REX::W32::MEM_RELEASE); }

		// override (IMemoryStore)
		auto Size(const void* a_mem) const
			-> std::size_t override;						// 0x01 - { return *static_cast<const std::size_t*>(a_mem) &
															// ~(static_cast<std::size_t>(3) << 62); }
		void GetMemoryStats(MemoryStats* a_stats) override; // 0x02 - { return; }
		auto ContainsBlockImpl(const void* a_block) const
			-> bool override; // 0x03 - { return baseAddress <= a_block && a_block <= endAddress; }
		auto AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment)
			-> void* override;							   // 0x04 - { return Allocate(a_size, a_alignment); }
		void DeallocateAlignImpl(void*& a_block) override; // 0x05 - { Deallocate(a_block), a_block = nullptr; }

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Allocate(std::size_t a_size, std::align_val_t a_alignment)
			-> void*;
		[[nodiscard]]
		__declspec(allocator)
		__declspec(restrict) auto CountedAllocate(std::size_t a_count, std::size_t a_size, std::align_val_t a_alignment)
			-> void*;
		__declspec(noalias) void Deallocate(void* a_mem);

		template <class T>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Allocate(
			std::size_t a_size = sizeof(T),
			std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) -> T*
		{
			return static_cast<T*>(Allocate(a_size, a_alignment));
		}

		template <class T>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto CountedAllocate(
			std::size_t a_count,
			std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) -> T*
		{
			return static_cast<T*>(CountedAllocate(a_count, sizeof(T), a_alignment));
		}

		// members
		std::array<FreeBlock*, 6> smallBlocks{nullptr}; // 0x08
		FreeTreeNode* freeList{nullptr};				// 0x38
		Block* lastBlock{nullptr};						// 0x40
		std::byte* baseAddress{nullptr};				// 0x48
		std::byte* endAddress{nullptr};					// 0x50
		std::byte* commitEnd{nullptr};					// 0x58
		std::size_t reserveSize;						// 0x60
		std::size_t minCommit{1 << 17};					// 0x68
		std::size_t totalAllocated{0};					// 0x70
		std::uint32_t keepPagesRequest{0};				// 0x78
		std::uint32_t totalFreeBlocks{0};				// 0x7C
		std::uint32_t freeSmallBlocks{0};				// 0x80
		std::uint32_t totalAllocatedBlocks{0};			// 0x84
		std::uint32_t pmpBarrier{0};					// 0x88
	};

	static_assert(sizeof(ScrapHeap) == 0x90);
}

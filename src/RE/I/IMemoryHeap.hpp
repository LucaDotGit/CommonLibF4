#pragma once

#include "RE/I/IMemoryStore.hpp"

namespace RE
{
	enum class MEM_CONTEXT : std::int32_t;

	class HeapStats;

	class __declspec(novtable) IMemoryHeap : public IMemoryStore // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMemoryHeap;
		inline static constexpr const auto& VTABLE = VTABLE::IMemoryHeap;

		~IMemoryHeap() override = default; // 0x00

		// override (IMemoryStore)
		auto ContainsBlockImpl(const void* a_block) const -> bool override // 0x03
		{
			return PointerInHeap(a_block);
		}

		auto AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) -> void* override // 0x04
		{
			return Allocate(a_size, a_alignment);
		}

		void DeallocateAlignImpl(void*& a_block) override // 0x05
		{
			Deallocate(a_block, 0);
		}

		// add
		virtual auto GetName() const -> const char* = 0;											  // 0x07
		virtual auto Allocate(std::size_t a_size, std::uint32_t a_alignment) -> void* = 0;			  // 0x08
		virtual void Deallocate(void* a_mem, std::uint32_t) = 0;									  // 0x09
		virtual auto PointerInHeap(const void* a_pointer) const -> bool = 0;						  // 0x0A
		virtual auto TotalSize(const void* a_pointer) const -> std::size_t = 0;						  // 0x0B
		virtual void GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) = 0;					  // 0x0C
		virtual auto ShouldTrySmallBlockPools(std::size_t a_size, MEM_CONTEXT a_context) -> bool = 0; // 0x0D
		virtual auto GetPageSize() const -> std::uint32_t = 0;										  // 0x0E
	};

	static_assert(sizeof(IMemoryHeap) == 0x08);
}

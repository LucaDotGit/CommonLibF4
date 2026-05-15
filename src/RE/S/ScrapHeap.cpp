#include "RE/S/ScrapHeap.hpp"

namespace RE
{
	__declspec(allocator) __declspec(restrict) void* ScrapHeap::Allocate(std::size_t a_size, std::align_val_t a_alignment)
	{
		using FuncType = void* (ScrapHeap::*)(std::size_t, std::align_val_t);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScrapHeap::Allocate };
		return std::invoke(FUNC, this, a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) void* ScrapHeap::CountedAllocate(std::size_t a_count, std::size_t a_size, std::align_val_t a_alignment)
	{
		auto* mem = Allocate(a_count * a_size, a_alignment);
		if (!mem) {
			return nullptr;
		}

		REL::MemWriteZero(mem, a_count * a_size);
		return mem;
	}

	__declspec(noalias) void ScrapHeap::Deallocate(void* a_mem)
	{
		using FuncType = decltype(&ScrapHeap::Deallocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScrapHeap::Deallocate };
		std::invoke(FUNC, this, a_mem);
	}
}

#include "RE/S/ScrapHeap.hpp"

namespace RE
{
	__declspec(allocator) __declspec(restrict) void* ScrapHeap::Allocate(std::size_t a_size, std::align_val_t a_alignment)
	{
		using FuncType = decltype(&ScrapHeap::Allocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScrapHeap::Allocate };
		return std::invoke(FUNC, this, a_size, a_alignment);
	}

	__declspec(noalias) void ScrapHeap::Deallocate(void* a_mem)
	{
		using FuncType = decltype(&ScrapHeap::Deallocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ScrapHeap::Deallocate };
		FUNC(this, a_mem);
	}
}

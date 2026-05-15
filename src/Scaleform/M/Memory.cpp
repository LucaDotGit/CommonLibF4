#include "Scaleform/M/Memory.hpp"

namespace Scaleform
{
	MemoryHeap*& Memory::GetGlobalHeap()
	{
		static const auto HEAP = REL::Relocation<MemoryHeap**>{ ID::Memory::Heap };
		return *HEAP;
	}

	bool Memory::ArenaIsEmpty(std::size_t a_arena)
	{
		return GetGlobalHeap()->ArenaIsEmpty(a_arena);
	}

	void Memory::CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc)
	{
		GetGlobalHeap()->CreateArena(a_arena, a_sysAlloc);
	}

	void Memory::DestroyArena(std::size_t a_arena)
	{
		GetGlobalHeap()->DestroyArena(a_arena);
	}

	MemoryHeap* Memory::GetHeapByAddress(const void* a_ptr)
	{
		return GetGlobalHeap()->GetAllocHeap(a_ptr);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::Alloc(std::size_t a_size)
	{
		return GetGlobalHeap()->Alloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::Alloc(std::size_t a_size, std::align_val_t a_alignment)
	{
		return GetGlobalHeap()->Alloc(a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::Alloc(std::size_t a_size, const AllocInfo& a_info)
	{
		return GetGlobalHeap()->Alloc(a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::Alloc(std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info)
	{
		return GetGlobalHeap()->Alloc(a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocAutoHeap(const void* a_ptr, std::size_t a_size)
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::align_val_t a_alignment)
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocAutoHeap(const void* a_ptr, std::size_t a_size, const AllocInfo& a_info)
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info)
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocInHeap(MemoryHeap* a_heap, std::size_t a_size)
	{
		return a_heap->Alloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::align_val_t a_alignment)
	{
		return a_heap->Alloc(a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, const AllocInfo& a_info)
	{
		return a_heap->Alloc(a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info)
	{
		return a_heap->Alloc(a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) void* Memory::Realloc(void* a_ptr, std::size_t a_newSize)
	{
		return GetGlobalHeap()->Realloc(a_ptr, a_newSize);
	}

	__declspec(noalias) void Memory::Free(void* a_ptr)
	{
		GetGlobalHeap()->Free(a_ptr);
	}

	__declspec(noalias) std::size_t Memory::GetSize(const void* a_ptr) noexcept
	{
		return GetGlobalHeap()->GetUsableSize(a_ptr);
	}

	__declspec(allocator) __declspec(restrict) void* malloc(std::size_t a_size) noexcept
	{
		try {
			return Memory::Alloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		try {
			return Memory::Alloc(a_size, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* calloc(std::size_t a_count, std::size_t a_size) noexcept
	{
		try {
			auto* mem = malloc(a_count * a_size);
			if (!mem) {
				return nullptr;
			}

			REL::MemWriteZero(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* realloc(void* a_ptr, std::size_t a_newSize) noexcept
	{
		try {
			return Memory::Realloc(a_ptr, a_newSize);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept
	{
		try {
			auto* mem = Memory::Realloc(a_ptr, a_newSize);
			if (!mem) {
				return nullptr;
			}

			if (std::align(static_cast<std::size_t>(a_alignment), 1, mem, a_newSize)) {
				return mem;
			}

			Memory::Free(mem);
			return nullptr;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void free(void* a_ptr) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			Memory::Free(a_ptr);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}

	__declspec(noalias) std::size_t msize(const void* a_ptr) noexcept
	{
		try {
			return Memory::GetSize(a_ptr);
		}
		catch (...) {
			return 0;
		}
	}
}

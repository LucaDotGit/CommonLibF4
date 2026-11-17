#include "Scaleform/M/Memory.hpp"

namespace Scaleform
{
	auto Memory::GetGlobalHeap() noexcept -> MemoryHeap*&
	{
		static const auto HEAP = REL::Relocation<MemoryHeap**>(ID::Memory::Heap);
		return *HEAP;
	}

	auto Memory::ArenaIsEmpty(std::size_t a_arena) -> bool
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

	auto Memory::GetHeapByAddress(const void* a_ptr) -> MemoryHeap*
	{
		return GetGlobalHeap()->GetAllocHeap(a_ptr);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::Alloc(std::size_t a_size) -> void*
	{
		return GetGlobalHeap()->Alloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::Alloc(std::size_t a_size, std::align_val_t a_alignment)
		-> void*
	{
		return GetGlobalHeap()->Alloc(a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::Alloc(std::size_t a_size, const AllocInfo& a_info) -> void*
	{
		return GetGlobalHeap()->Alloc(a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::Alloc(
		std::size_t a_size,
		std::align_val_t a_alignment,
		const AllocInfo& a_info) -> void*
	{
		return GetGlobalHeap()->Alloc(a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocAutoHeap(const void* a_ptr, std::size_t a_size)
		-> void*
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocAutoHeap(
		const void* a_ptr,
		std::size_t a_size,
		std::align_val_t a_alignment) -> void*
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocAutoHeap(
		const void* a_ptr,
		std::size_t a_size,
		const AllocInfo& a_info) -> void*
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocAutoHeap(
		const void* a_ptr,
		std::size_t a_size,
		std::align_val_t a_alignment,
		const AllocInfo& a_info) -> void*
	{
		return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocInHeap(MemoryHeap* a_heap, std::size_t a_size) -> void*
	{
		return a_heap->Alloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocInHeap(
		MemoryHeap* a_heap,
		std::size_t a_size,
		std::align_val_t a_alignment) -> void*
	{
		return a_heap->Alloc(a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocInHeap(
		MemoryHeap* a_heap,
		std::size_t a_size,
		const AllocInfo& a_info) -> void*
	{
		return a_heap->Alloc(a_size, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::AllocInHeap(
		MemoryHeap* a_heap,
		std::size_t a_size,
		std::align_val_t a_alignment,
		const AllocInfo& a_info) -> void*
	{
		return a_heap->Alloc(a_size, a_alignment, std::addressof(a_info));
	}

	__declspec(allocator) __declspec(restrict) auto Memory::Realloc(void* a_ptr, std::size_t a_newSize) -> void*
	{
		return GetGlobalHeap()->Realloc(a_ptr, a_newSize);
	}

	__declspec(noalias) void Memory::Free(void* a_ptr)
	{
		GetGlobalHeap()->Free(a_ptr);
	}

	__declspec(noalias) auto Memory::GetSize(const void* a_ptr) noexcept -> std::size_t
	{
		return GetGlobalHeap()->GetUsableSize(a_ptr);
	}

	__declspec(allocator) __declspec(restrict) auto malloc(std::size_t a_size) noexcept -> void*
	{
		try {
			return Memory::Alloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto aligned_alloc(std::size_t a_size, std::align_val_t a_alignment)
		noexcept -> void*
	{
		try {
			return Memory::Alloc(a_size, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto calloc(std::size_t a_count, std::size_t a_size) noexcept -> void*
	{
		try {
			auto* mem = malloc(a_count * a_size);
			if (!mem) {
				return nullptr;
			}

			REL::WriteZeros(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto realloc(void* a_ptr, std::size_t a_newSize) noexcept -> void*
	{
		try {
			return Memory::Realloc(a_ptr, a_newSize);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto aligned_realloc(
		void* a_ptr,
		std::size_t a_newSize,
		std::align_val_t a_alignment) noexcept -> void*
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

	__declspec(noalias) auto msize(const void* a_ptr) noexcept -> std::size_t
	{
		try {
			return Memory::GetSize(a_ptr);
		}
		catch (...) {
			return 0;
		}
	}
}

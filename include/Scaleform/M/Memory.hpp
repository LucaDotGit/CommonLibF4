#pragma once

#include "Scaleform/M/MemoryHeap.hpp"

namespace Scaleform
{
	class Memory
	{
	public:
		[[nodiscard]] static MemoryHeap*& GetGlobalHeap();

		[[nodiscard]] static bool ArenaIsEmpty(std::size_t a_arena);
		static void CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc);
		static void DestroyArena(std::size_t a_arena);

		[[nodiscard]] static MemoryHeap* GetHeapByAddress(const void* a_ptr);

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* Alloc(std::size_t a_size);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* Alloc(std::size_t a_size, std::align_val_t a_alignment);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* Alloc(std::size_t a_size, const AllocInfo& a_info);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* Alloc(std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info);

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocAutoHeap(const void* a_ptr, std::size_t a_size);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::align_val_t a_alignment);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, const AllocInfo& a_info);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info);

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::align_val_t a_alignment);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, const AllocInfo& a_info);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::align_val_t a_alignment, const AllocInfo& a_info);

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* Realloc(void* a_ptr, std::size_t a_newSize);

		__declspec(noalias) static void Free(void* a_ptr);

		[[nodiscard]] __declspec(noalias) static std::size_t GetSize(const void* a_ptr) noexcept;
	};
	static_assert(std::is_empty_v<Memory>);

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* malloc(std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* malloc() noexcept
	{
		return static_cast<T*>(malloc(sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* aligned_alloc(std::size_t a_size = sizeof(T), std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(aligned_alloc(a_size, a_alignment));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* calloc(std::size_t a_count, std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* calloc(std::size_t a_count) noexcept
	{
		return static_cast<T*>(calloc(a_count, sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* realloc(void* a_ptr, std::size_t a_newSize) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* realloc(T* a_ptr, std::size_t a_newSize = sizeof(T)) noexcept
	{
		return static_cast<T*>(realloc(static_cast<void*>(a_ptr), a_newSize));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* aligned_realloc(T* a_ptr, std::size_t a_newSize = sizeof(T), std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(aligned_realloc(static_cast<void*>(a_ptr), a_newSize, a_alignment));
	}

	__declspec(noalias) void free(void* a_ptr) noexcept;

	[[nodiscard]] __declspec(noalias) std::size_t msize(const void* a_ptr) noexcept;

	template <class T>
	struct StlAllocator
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] std::size_t a_count) noexcept
		{
			free(static_cast<void*>(a_ptr));
		}
	};

	template <class T>
	struct StlAlignedAllocator
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = aligned_alloc<value_type>(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] std::size_t a_count) noexcept
		{
			free(static_cast<void*>(a_ptr));
		}
	};
}

#define SF_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                                                       \
	{                                                                                                                   \
		auto* mem = Scaleform::malloc(a_size);                                                                          \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                                                     \
	{                                                                                                                   \
		auto* mem = Scaleform::malloc(a_size);                                                                          \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t a_alignment) noexcept                         \
	{                                                                                                                   \
		auto* mem = Scaleform::aligned_alloc(a_size, a_alignment);                                                      \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t a_alignment) noexcept                       \
	{                                                                                                                   \
		auto* mem = Scaleform::aligned_alloc(a_size, a_alignment);                                                      \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                                        \
	void operator delete(void* a_ptr) noexcept { Scaleform::free(a_ptr); }                                              \
	void operator delete[](void* a_ptr) noexcept { Scaleform::free(a_ptr); }                                            \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { Scaleform::free(a_ptr); }                            \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { Scaleform::free(a_ptr); }                          \
	void operator delete(void* a_ptr, std::size_t) noexcept { Scaleform::free(a_ptr); }                                 \
	void operator delete[](void* a_ptr, std::size_t) noexcept { Scaleform::free(a_ptr); }                               \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { Scaleform::free(a_ptr); }               \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { Scaleform::free(a_ptr); }

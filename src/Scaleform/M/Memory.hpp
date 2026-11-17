#pragma once

#include "Scaleform/M/MemoryHeap.hpp"

namespace Scaleform
{
	class Memory
	{
	public:
		[[nodiscard]]
		static auto GetGlobalHeap() noexcept -> MemoryHeap*&;

		[[nodiscard]]
		static auto ArenaIsEmpty(std::size_t a_arena) -> bool;
		static void CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc);
		static void DestroyArena(std::size_t a_arena);

		[[nodiscard]]
		static auto GetHeapByAddress(const void* a_ptr) -> MemoryHeap*;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto Alloc(std::size_t a_size) -> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto Alloc(std::size_t a_size, std::align_val_t a_alignment)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto Alloc(std::size_t a_size, const AllocInfo& a_info)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto Alloc(
			std::size_t a_size,
			std::align_val_t a_alignment,
			const AllocInfo& a_info) -> void*;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocAutoHeap(const void* a_ptr, std::size_t a_size)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocAutoHeap(
			const void* a_ptr,
			std::size_t a_size,
			std::align_val_t a_alignment) -> void*;
		[[nodiscard]]
		__declspec(allocator)
		__declspec(restrict) static auto AllocAutoHeap(const void* a_ptr, std::size_t a_size, const AllocInfo& a_info)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocAutoHeap(
			const void* a_ptr,
			std::size_t a_size,
			std::align_val_t a_alignment,
			const AllocInfo& a_info) -> void*;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocInHeap(MemoryHeap* a_heap, std::size_t a_size)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocInHeap(
			MemoryHeap* a_heap,
			std::size_t a_size,
			std::align_val_t a_alignment) -> void*;
		[[nodiscard]]
		__declspec(allocator)
		__declspec(restrict) static auto AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, const AllocInfo& a_info)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto AllocInHeap(
			MemoryHeap* a_heap,
			std::size_t a_size,
			std::align_val_t a_alignment,
			const AllocInfo& a_info) -> void*;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) static auto Realloc(void* a_ptr, std::size_t a_newSize) -> void*;

		__declspec(noalias) static void Free(void* a_ptr);

		[[nodiscard]]
		__declspec(noalias) static auto GetSize(const void* a_ptr) noexcept -> std::size_t;
	};

	static_assert(std::is_empty_v<Memory>);

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto malloc(std::size_t a_size) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto malloc() noexcept -> T*
	{
		return static_cast<T*>(malloc(sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto aligned_alloc(
		std::size_t a_size = sizeof(T),
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(aligned_alloc(a_size, a_alignment));
	}

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto calloc(std::size_t a_count, std::size_t a_size) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(calloc(a_count, sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto realloc(void* a_ptr, std::size_t a_newSize) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto realloc(T* a_ptr, std::size_t a_newSize = sizeof(T)) noexcept -> T*
	{
		return static_cast<T*>(realloc(static_cast<void*>(a_ptr), a_newSize));
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept
		-> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto aligned_realloc(
		T* a_ptr,
		std::size_t a_newSize = sizeof(T),
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(aligned_realloc(static_cast<void*>(a_ptr), a_newSize, a_alignment));
	}

	__declspec(noalias) void free(void* a_ptr) noexcept;

	[[nodiscard]]
	__declspec(noalias) auto msize(const void* a_ptr) noexcept -> std::size_t;

	template <class T>
	struct StlAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr StlAllocator() noexcept = default;
		constexpr ~StlAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StlAllocator([[maybe_unused]] const StlAllocator<U>& a_other) noexcept
		{
		}

		constexpr StlAllocator(const StlAllocator&) noexcept = default;
		constexpr StlAllocator(StlAllocator&&) noexcept = default;

		constexpr auto operator=(const StlAllocator&) noexcept -> StlAllocator& = default;
		constexpr auto operator=(StlAllocator&&) noexcept -> StlAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			return mem;
		}

		[[nodiscard]]
		auto allocate_at_least(size_type a_count) -> std::allocation_result<value_type*, size_type>
		{
			return {allocate(a_count), a_count};
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const StlAllocator<T1>& a_lhs,
		[[maybe_unused]] const StlAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}

	template <class T>
	struct StlAlignedAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr StlAlignedAllocator() noexcept = default;
		constexpr ~StlAlignedAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StlAlignedAllocator([[maybe_unused]] const StlAlignedAllocator<U>& a_other) noexcept
		{
		}

		constexpr StlAlignedAllocator(const StlAlignedAllocator&) noexcept = default;
		constexpr StlAlignedAllocator(StlAlignedAllocator&&) noexcept = default;

		constexpr auto operator=(const StlAlignedAllocator&) noexcept -> StlAlignedAllocator& = default;
		constexpr auto operator=(StlAlignedAllocator&&) noexcept -> StlAlignedAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = aligned_alloc<value_type>(
				a_count * sizeof(value_type),
				static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			return mem;
		}

		[[nodiscard]]
		auto allocate_at_least(size_type a_count) -> std::allocation_result<value_type*, size_type>
		{
			return {allocate(a_count), a_count};
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const StlAlignedAllocator<T1>& a_lhs,
		[[maybe_unused]] const StlAlignedAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}
}

#define SCALEFORM_HEAP_REDEFINE_NEW(a_type)                                                                            \
	static_assert(std::is_class_v<a_type>);                                                                            \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new(std::size_t a_size)                                                                              \
		->void*                                                                                                        \
	{                                                                                                                  \
		auto* mem = ::Scaleform::malloc(a_size);                                                                       \
		if (!mem) [[unlikely]] {                                                                                       \
			::REX::Throw<std::bad_alloc>();                                                                            \
		}                                                                                                              \
                                                                                                                       \
		return mem;                                                                                                    \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new[](std::size_t a_size)                                                                            \
		->void*                                                                                                        \
	{                                                                                                                  \
		auto* mem = ::Scaleform::malloc(a_size);                                                                       \
		if (!mem) [[unlikely]] {                                                                                       \
			::REX::Throw<std::bad_alloc>();                                                                            \
		}                                                                                                              \
                                                                                                                       \
		return mem;                                                                                                    \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment)                                                \
		->void*                                                                                                        \
	{                                                                                                                  \
		auto* mem = ::Scaleform::aligned_alloc(a_size, a_alignment);                                                   \
		if (!mem) [[unlikely]] {                                                                                       \
			::REX::Throw<std::bad_alloc>();                                                                            \
		}                                                                                                              \
                                                                                                                       \
		return mem;                                                                                                    \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new[](std::size_t a_size, std::align_val_t a_alignment)                                              \
		->void*                                                                                                        \
	{                                                                                                                  \
		auto* mem = ::Scaleform::aligned_alloc(a_size, a_alignment);                                                   \
		if (!mem) [[unlikely]] {                                                                                       \
			::REX::Throw<std::bad_alloc>();                                                                            \
		}                                                                                                              \
                                                                                                                       \
		return mem;                                                                                                    \
	}                                                                                                                  \
	[[nodiscard]]                                                                                                      \
	auto operator new(std::size_t a_size, std::nothrow_t /*a_nothrow*/) noexcept -> void*                              \
	{                                                                                                                  \
		return ::Scaleform::malloc(a_size);                                                                            \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new[](std::size_t a_size, std::nothrow_t /*a_nothrow*/) noexcept -> void*                            \
	{                                                                                                                  \
		return ::Scaleform::malloc(a_size);                                                                            \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment, std::nothrow_t /*a_nothrow*/) noexcept         \
		-> void*                                                                                                       \
	{                                                                                                                  \
		return ::Scaleform::aligned_alloc(a_size, a_alignment);                                                        \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	auto operator new[](std::size_t a_size, std::align_val_t a_alignment, std::nothrow_t /*a_nothrow*/) noexcept       \
		-> void*                                                                                                       \
	{                                                                                                                  \
		return ::Scaleform::aligned_alloc(a_size, a_alignment);                                                        \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                                 \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                               \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept        \
		-> void*                                                                                                       \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept      \
		-> void*                                                                                                       \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, std::nothrow_t /*a_nothrow*/) noexcept -> void*   \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, std::nothrow_t /*a_nothrow*/) noexcept -> void* \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new(                                                                                       \
		std::size_t /*a_size*/,                                                                                        \
		std::align_val_t /*a_alignment*/,                                                                              \
		void* a_ptr,                                                                                                   \
		std::nothrow_t /*a_nothrow*/) noexcept -> void*                                                                \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	[[nodiscard]]                                                                                                      \
	constexpr auto operator new[](                                                                                     \
		std::size_t /*a_size*/,                                                                                        \
		std::align_val_t /*a_alignment*/,                                                                              \
		void* a_ptr,                                                                                                   \
		std::nothrow_t /*a_nothrow*/) noexcept -> void*                                                                \
	{                                                                                                                  \
		return a_ptr;                                                                                                  \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete(void* a_ptr) noexcept                                                                         \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete[](void* a_ptr) noexcept                                                                       \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                       \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                     \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete(void* a_ptr, std::size_t /*a_size*/) noexcept                                                 \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/) noexcept                                               \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept               \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept             \
	{                                                                                                                  \
		::Scaleform::free(a_ptr);                                                                                      \
	}

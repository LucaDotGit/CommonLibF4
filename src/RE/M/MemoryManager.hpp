#pragma once

#include "RE/S/ScrapHeap.hpp"

namespace RE::CompactingStore
{
	class Store;
}

namespace RE
{
	class BSSmallBlockAllocator;
	class IMemoryHeap;

	class MemoryManager
	{
	public:
		class AutoScrapBuffer
		{
		public:
			inline static constexpr auto SCRAP_HEAP_ALIGNMENT =
				static_cast<std::align_val_t>(alignof(std::max_align_t));

			using value_type = std::byte;
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using const_pointer = const value_type*;

			AutoScrapBuffer() noexcept = default;

			explicit AutoScrapBuffer(std::size_t a_size, std::align_val_t a_alignment = SCRAP_HEAP_ALIGNMENT);

			template <class T>
			explicit AutoScrapBuffer(
				std::size_t a_size,
				std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) :
				AutoScrapBuffer(a_size, a_alignment)
			{
			}

			~AutoScrapBuffer() noexcept;

			AutoScrapBuffer(const AutoScrapBuffer&) = delete;
			AutoScrapBuffer(AutoScrapBuffer&& a_rhs) noexcept;

			auto operator=(const AutoScrapBuffer&) -> AutoScrapBuffer& = delete;
			auto operator=(AutoScrapBuffer&& a_rhs) noexcept -> AutoScrapBuffer&;

			[[nodiscard]]
			explicit operator bool() const noexcept
			{
				return _data != nullptr;
			}

			[[nodiscard]]
			auto data() noexcept -> pointer
			{
				return _data;
			}

			[[nodiscard]]
			auto data() const noexcept -> const_pointer
			{
				return _data;
			}

			[[nodiscard]]
			auto release() noexcept -> pointer;

			[[nodiscard]]
			__declspec(allocator)
			__declspec(restrict) auto allocate_bytes(size_type a_count, std::align_val_t a_alignment) noexcept
				-> pointer;

			__declspec(noalias) void deallocate_bytes(pointer a_mem) noexcept;

		private:
			// members
			pointer _data{nullptr}; // 0x00
		};

		static_assert(sizeof(AutoScrapBuffer) == 0x08);

		class ThreadScrapHeap
		{
		public:
			// members
			ScrapHeap heap;													  // 0x00
			ThreadScrapHeap* next{nullptr};									  // 0x90
			REX::W32::THREAD_ID owningThread{REX::W32::GetCurrentThreadId()}; // 0x98
		};

		static_assert(sizeof(ThreadScrapHeap) == 0xA0);

		[[nodiscard]]
		static auto GetSingleton() -> MemoryManager&;

		void RegisterMemoryManager();
		[[nodiscard]]
		auto GetThreadScrapHeap() -> ScrapHeap*;
		[[nodiscard]]
		auto GetSmallBlockAllocator() const -> BSSmallBlockAllocator*;
		[[nodiscard]]
		__declspec(allocator)
		__declspec(restrict) auto Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
			-> void*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto Reallocate(
			void* a_oldMem,
			std::size_t a_newSize,
			std::uint32_t a_alignment,
			bool a_alignmentRequired) -> void*;
		__declspec(noalias) void Deallocate(void* a_mem, bool a_alignmentRequired);
		[[nodiscard]]
		__declspec(noalias) auto Size(const void* a_ptr) const -> std::size_t;

		// members
		bool initialized{false};							   // 0x000
		std::uint16_t numHeaps{0};							   // 0x002
		std::uint16_t numPhysicalHeaps{0};					   // 0x004
		IMemoryHeap** heaps{nullptr};						   // 0x008
		bool* allowOtherContextAllocs{nullptr};				   // 0x010
		std::array<IMemoryHeap*, 127> heapsByContext{nullptr}; // 0x018
		ThreadScrapHeap* threadScrapHeap{nullptr};			   // 0x410
		IMemoryHeap** physicalHeaps{nullptr};				   // 0x418
		IMemoryHeap* bigAllocHeap{nullptr};					   // 0x420
		IMemoryHeap* emergencyHeap{nullptr};				   // 0x428
		BSSmallBlockAllocator* smallBlockAllocator{nullptr};   // 0x430
		CompactingStore::Store* compactingStore{nullptr};	   // 0x438
		IMemoryHeap* externalHavokAllocator{nullptr};		   // 0x440
		bool specialHeaps{false};							   // 0x448
		bool allowPoolUse{true};							   // 0x449
		std::uint32_t sysAllocBytes{0};						   // 0x44C
		std::uint32_t mallocBytes{0};						   // 0x450
		std::uint32_t alignmentForPools{4};					   // 0x454
		std::uint32_t mainThreadMemoryProblemPassSignal{0};	   // 0x458
		std::size_t failedAllocationSize{0};				   // 0x460
		std::uint32_t numMemoryProblemPassesRun{0};			   // 0x468
		std::size_t timeOfLastMemoryProblemPass{0};			   // 0x470
		IMemoryHeap* defaultHeap{nullptr};					   // 0x478
	};

	static_assert(sizeof(MemoryManager) == 0x480);

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

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto scrap_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto scrap_alloc(
		std::size_t a_count,
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(scrap_alloc(a_count * sizeof(T), a_alignment));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto scrap_alloc(
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(scrap_alloc(sizeof(T), a_alignment));
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto scrap_calloc(std::size_t a_count, std::size_t a_size, std::align_val_t a_alignment)
		noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto scrap_calloc(
		std::size_t a_count,
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(scrap_calloc(a_count, sizeof(T), a_alignment));
	}

	__declspec(noalias) void free(void* a_ptr) noexcept;
	__declspec(noalias) void aligned_free(void* a_ptr) noexcept;
	__declspec(noalias) void scrap_free(void* a_ptr) noexcept;

	[[nodiscard]]
	__declspec(noalias) auto msize(const void* a_ptr) noexcept -> std::size_t;

	[[nodiscard]]
	__declspec(noalias) auto scrap_msize(const void* a_ptr) noexcept -> std::size_t;

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
			aligned_free(static_cast<void*>(a_ptr));
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

	template <class T>
	struct StlScrapAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::false_type;

		constexpr StlScrapAllocator() noexcept = default;
		constexpr ~StlScrapAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StlScrapAllocator([[maybe_unused]] const StlScrapAllocator<U>& a_other) noexcept
		{
		}

		constexpr StlScrapAllocator(const StlScrapAllocator&) noexcept = default;
		constexpr StlScrapAllocator(StlScrapAllocator&&) noexcept = default;

		constexpr auto operator=(const StlScrapAllocator&) noexcept -> StlScrapAllocator& = default;
		constexpr auto operator=(StlScrapAllocator&&) noexcept -> StlScrapAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = scrap_alloc<value_type>(
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
			scrap_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const StlScrapAllocator<T1>& a_lhs,
		[[maybe_unused]] const StlScrapAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}
}

#define GAME_HEAP_REDEFINE_NEW(a_type)                                                                                \
	static_assert(std::is_class_v<a_type>);                                                                           \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size)                                                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::malloc(a_size);                                                                             \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size)                                                                           \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::malloc(a_size);                                                                             \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment)                                               \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, a_alignment);                                                         \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, std::align_val_t a_alignment)                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, a_alignment);                                                         \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                      \
	{                                                                                                                 \
		return ::RE::malloc(a_size);                                                                                  \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                    \
	{                                                                                                                 \
		return ::RE::malloc(a_size);                                                                                  \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, a_alignment);                                                              \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](                                                                                              \
		std::size_t a_size,                                                                                           \
		std::align_val_t a_alignment,                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, a_alignment);                                                              \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                                \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                              \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept       \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept     \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept    \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept  \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(                                                                                      \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](                                                                                    \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr) noexcept                                                                        \
	{                                                                                                                 \
		::RE::free(a_ptr);                                                                                            \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr) noexcept                                                                      \
	{                                                                                                                 \
		::RE::free(a_ptr);                                                                                            \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                      \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                    \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                           \
	{                                                                                                                 \
		::RE::free(a_ptr);                                                                                            \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                         \
	{                                                                                                                 \
		::RE::free(a_ptr);                                                                                            \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept              \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept            \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}

#define GAME_HEAP_REDEFINE_ALIGNED_NEW(a_type)                                                                        \
	static_assert(std::is_class_v<a_type>);                                                                           \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size)                                                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type)));                      \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size)                                                                           \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type)));                      \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment)                                               \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, a_alignment);                                                         \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, std::align_val_t a_alignment)                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::aligned_alloc(a_size, a_alignment);                                                         \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                      \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type)));                           \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                    \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type)));                           \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, a_alignment);                                                              \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](                                                                                              \
		std::size_t a_size,                                                                                           \
		std::align_val_t a_alignment,                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return ::RE::aligned_alloc(a_size, a_alignment);                                                              \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                                \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                              \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept       \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept     \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept    \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept  \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(                                                                                      \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](                                                                                    \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr) noexcept                                                                        \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr) noexcept                                                                      \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                      \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                    \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                           \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                         \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept              \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept            \
	{                                                                                                                 \
		::RE::aligned_free(a_ptr);                                                                                    \
	}

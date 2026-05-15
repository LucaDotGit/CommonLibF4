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
			inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(alignof(std::max_align_t));

			AutoScrapBuffer() noexcept = default;

			AutoScrapBuffer(std::size_t a_size, std::align_val_t a_alignment = SCRAP_HEAP_ALIGNMENT);

			template <class T>
			AutoScrapBuffer(std::size_t a_size, std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T)))
				: AutoScrapBuffer(a_size, a_alignment)
			{
			}

			~AutoScrapBuffer() noexcept;

			AutoScrapBuffer(const AutoScrapBuffer&) = delete;
			AutoScrapBuffer(AutoScrapBuffer&& a_rhs) noexcept;

			AutoScrapBuffer& operator=(const AutoScrapBuffer&) = delete;
			AutoScrapBuffer& operator=(AutoScrapBuffer&& a_rhs) noexcept;

			[[nodiscard]] explicit operator bool() const noexcept { return _data != nullptr; }

			[[nodiscard]] void* data() noexcept { return _data; }
			[[nodiscard]] const void* data() const noexcept { return _data; }

			[[nodiscard]] void* release() noexcept
			{
				auto* mem = _data;
				_data = nullptr;
				return mem;
			}

			[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(std::size_t a_size, std::align_val_t a_alignment) noexcept;
			__declspec(noalias) static void deallocate_bytes(void* a_mem) noexcept;

		private:
			// members
			void* _data{ nullptr }; // 00
		};
		static_assert(sizeof(AutoScrapBuffer) == 0x08);

		class ThreadScrapHeap
		{
		public:
			// members
			ScrapHeap heap;														// 00
			ThreadScrapHeap* next{ nullptr };									// 90
			REX::W32::THREAD_ID owningThread{ REX::W32::GetCurrentThreadId() }; // 98
		};
		static_assert(sizeof(ThreadScrapHeap) == 0xA0);

		[[nodiscard]] static MemoryManager& GetSingleton();

		void RegisterMemoryManager();
		[[nodiscard]] ScrapHeap* GetThreadScrapHeap();
		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired);
		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired);
		__declspec(noalias) void Deallocate(void* a_mem, bool a_alignmentRequired);
		[[nodiscard]] __declspec(noalias) std::size_t Size(const void* a_ptr) const;

		// members
		bool initialized{ false };								 // 000
		std::uint16_t numHeaps{ 0 };							 // 002
		std::uint16_t numPhysicalHeaps{ 0 };					 // 004
		IMemoryHeap** heaps{ nullptr };							 // 008
		bool* allowOtherContextAllocs{ nullptr };				 // 010
		std::array<IMemoryHeap*, 127> heapsByContext{ nullptr }; // 018
		ThreadScrapHeap* threadScrapHeap{ nullptr };			 // 410
		IMemoryHeap** physicalHeaps{ nullptr };					 // 418
		IMemoryHeap* bigAllocHeap{ nullptr };					 // 420
		IMemoryHeap* emergencyHeap{ nullptr };					 // 428
		BSSmallBlockAllocator* smallBlockAllocator{ nullptr };	 // 430
		CompactingStore::Store* compactingStore{ nullptr };		 // 438
		IMemoryHeap* externalHavokAllocator{ nullptr };			 // 440
		bool specialHeaps{ false };								 // 448
		bool allowPoolUse{ true };								 // 449
		std::uint32_t sysAllocBytes{ 0 };						 // 44C
		std::uint32_t mallocBytes{ 0 };							 // 450
		std::uint32_t alignmentForPools{ 4 };					 // 454
		std::uint32_t mainThreadMemoryProblemPassSignal{ 0 };	 // 458
		std::size_t failedAllocationSize{ 0 };					 // 460
		std::uint32_t numMemoryProblemPassesRun{ 0 };			 // 468
		std::size_t timeOfLastMemoryProblemPass{ 0 };			 // 470
		IMemoryHeap* defaultHeap{ nullptr };					 // 478
	};
	static_assert(sizeof(MemoryManager) == 0x480);

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

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* scrap_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* scrap_alloc(std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(scrap_alloc(sizeof(T), a_alignment));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* scrap_calloc(std::size_t a_count, std::size_t a_size, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* scrap_calloc(std::size_t a_count, std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(scrap_calloc(a_count, sizeof(T), a_alignment));
	}

	__declspec(noalias) void free(void* a_ptr) noexcept;
	__declspec(noalias) void aligned_free(void* a_ptr) noexcept;
	__declspec(noalias) void scrap_free(void* a_ptr) noexcept;

	[[nodiscard]] __declspec(noalias) std::size_t msize(const void* a_ptr) noexcept;

	[[nodiscard]] __declspec(noalias) std::size_t scrap_msize(const void* a_ptr) noexcept;

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

		constexpr StlAllocator(const StlAllocator&) noexcept = default;
		constexpr StlAllocator(StlAllocator&&) noexcept = default;

		constexpr StlAllocator& operator=(const StlAllocator&) noexcept = default;
		constexpr StlAllocator& operator=(StlAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const StlAllocator<T1>& a_lhs, [[maybe_unused]] const StlAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const StlAllocator<T1>& a_lhs, [[maybe_unused]] const StlAllocator<T2>& a_rhs) noexcept
	{
		return false;
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

		constexpr StlAlignedAllocator(const StlAlignedAllocator&) noexcept = default;
		constexpr StlAlignedAllocator(StlAlignedAllocator&&) noexcept = default;

		constexpr StlAlignedAllocator& operator=(const StlAlignedAllocator&) noexcept = default;
		constexpr StlAlignedAllocator& operator=(StlAlignedAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = aligned_alloc<value_type>(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			aligned_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const StlAlignedAllocator<T1>& a_lhs, [[maybe_unused]] const StlAlignedAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const StlAlignedAllocator<T1>& a_lhs, [[maybe_unused]] const StlAlignedAllocator<T2>& a_rhs) noexcept
	{
		return false;
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

		constexpr StlScrapAllocator(const StlScrapAllocator&) noexcept = default;
		constexpr StlScrapAllocator(StlScrapAllocator&&) noexcept = default;

		constexpr StlScrapAllocator& operator=(const StlScrapAllocator&) noexcept = default;
		constexpr StlScrapAllocator& operator=(StlScrapAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = scrap_alloc<value_type>(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			scrap_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const StlScrapAllocator<T1>& a_lhs, [[maybe_unused]] const StlScrapAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const StlScrapAllocator<T1>& a_lhs, [[maybe_unused]] const StlScrapAllocator<T2>& a_rhs) noexcept
	{
		return false;
	}
}

#define GAME_HEAP_REDEFINE_HELPER(a_type)                                                                               \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t a_alignment)                                  \
	{                                                                                                                   \
		auto* mem = RE::aligned_alloc(a_size, a_alignment);                                                             \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t a_alignment)                                \
	{                                                                                                                   \
		auto* mem = RE::aligned_alloc(a_size, a_alignment);                                                             \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
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
	void operator delete(void*, void*) noexcept { return; }                                                             \
	void operator delete[](void*, void*) noexcept { return; }                                                           \
                                                                                                                        \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }                           \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }                         \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }              \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }

#define GAME_HEAP_REDEFINE_NEW(a_type)                                             \
	[[nodiscard]] void* operator new(std::size_t a_size)                           \
	{                                                                              \
		auto* mem = RE::malloc(a_size);                                            \
		if (!mem) [[unlikely]] {                                                   \
			throw std::bad_alloc();                                                \
		}                                                                          \
                                                                                   \
		return mem;                                                                \
	}                                                                              \
                                                                                   \
	[[nodiscard]] void* operator new[](std::size_t a_size)                         \
	{                                                                              \
		auto* mem = RE::malloc(a_size);                                            \
		if (!mem) [[unlikely]] {                                                   \
			throw std::bad_alloc();                                                \
		}                                                                          \
                                                                                   \
		return mem;                                                                \
	}                                                                              \
                                                                                   \
	void operator delete(void* a_ptr) noexcept { RE::free(a_ptr); }                \
	void operator delete[](void* a_ptr) noexcept { RE::free(a_ptr); }              \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::free(a_ptr); }   \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::free(a_ptr); } \
                                                                                   \
	GAME_HEAP_REDEFINE_HELPER(a_type)

#define GAME_HEAP_REDEFINE_ALIGNED_NEW(a_type)                                                 \
	[[nodiscard]] void* operator new(std::size_t a_size)                                       \
	{                                                                                          \
		auto* mem = RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type))); \
		if (!mem) [[unlikely]] {                                                               \
			throw std::bad_alloc();                                                            \
		}                                                                                      \
                                                                                               \
		return mem;                                                                            \
	}                                                                                          \
                                                                                               \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                     \
	{                                                                                          \
		auto* mem = RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type))); \
		if (!mem) [[unlikely]] {                                                               \
			throw std::bad_alloc();                                                            \
		}                                                                                      \
                                                                                               \
		return mem;                                                                            \
	}                                                                                          \
                                                                                               \
	void operator delete(void* a_ptr) noexcept { RE::aligned_free(a_ptr); }                    \
	void operator delete[](void* a_ptr) noexcept { RE::aligned_free(a_ptr); }                  \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::aligned_free(a_ptr); }       \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::aligned_free(a_ptr); }     \
                                                                                               \
	GAME_HEAP_REDEFINE_HELPER(a_type)

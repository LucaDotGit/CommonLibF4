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

			[[nodiscard]] static void* allocate(std::size_t a_size, std::align_val_t a_alignment) noexcept;
			static void deallocate(void* a_mem) noexcept;

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

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* scrap_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* scrap_alloc(std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(scrap_alloc(sizeof(T), a_alignment));
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
	__declspec(noalias) void aligned_free(void* a_ptr) noexcept;
	__declspec(noalias) void scrap_free(void* a_ptr) noexcept;

	[[nodiscard]] __declspec(noalias) std::size_t msize(const void* a_ptr) noexcept;

	[[nodiscard]] __declspec(noalias) std::size_t scrap_msize(const void* a_ptr) noexcept;

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
			aligned_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T>
	struct StlScrapAllocator
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = scrap_alloc<value_type>(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] std::size_t a_count) noexcept
		{
			scrap_free(static_cast<void*>(a_ptr));
		}
	};
}

#define GAME_HEAP_REDEFINE_HELPER(a_type)                                                                               \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t a_alignment) noexcept                         \
	{                                                                                                                   \
		auto* mem = RE::aligned_alloc(a_size, a_alignment);                                                             \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t a_alignment) noexcept                       \
	{                                                                                                                   \
		auto* mem = RE::aligned_alloc(a_size, a_alignment);                                                             \
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
	void operator delete(void*, void*) noexcept { return; }                                                             \
	void operator delete[](void*, void*) noexcept { return; }                                                           \
                                                                                                                        \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }                           \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }                         \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }              \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::aligned_free(a_ptr); }

#define GAME_HEAP_REDEFINE_NEW(a_type)                                             \
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                  \
	{                                                                              \
		auto* mem = RE::malloc(a_size);                                            \
		if (!mem) [[unlikely]] {                                                   \
			REX::AllocationFail();                                                 \
		}                                                                          \
                                                                                   \
		return mem;                                                                \
	}                                                                              \
                                                                                   \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                \
	{                                                                              \
		auto* mem = RE::malloc(a_size);                                            \
		if (!mem) [[unlikely]] {                                                   \
			REX::AllocationFail();                                                 \
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
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                              \
	{                                                                                          \
		auto* mem = RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type))); \
		if (!mem) [[unlikely]] {                                                               \
			REX::AllocationFail();                                                             \
		}                                                                                      \
                                                                                               \
		return mem;                                                                            \
	}                                                                                          \
                                                                                               \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                            \
	{                                                                                          \
		auto* mem = RE::aligned_alloc(a_size, static_cast<std::align_val_t>(alignof(a_type))); \
		if (!mem) [[unlikely]] {                                                               \
			REX::AllocationFail();                                                             \
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

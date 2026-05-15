#pragma once

namespace RE::Impl
{
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* NiMalloc(std::size_t a_size);
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* NiAlignedAlloc(std::size_t a_size, std::align_val_t a_alignment);
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* NiRealloc(void* a_ptr, std::size_t a_newSize);
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* NiAlignedRealloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment);
	__declspec(noalias) void NiFree(void* a_ptr);
}

namespace RE
{
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* ni_malloc(std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(ni_malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_malloc() noexcept
	{
		return static_cast<T*>(ni_malloc(sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* ni_aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_aligned_alloc(std::size_t a_size = sizeof(T), std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(ni_aligned_alloc(a_size, a_alignment));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* ni_calloc(std::size_t a_count, std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_calloc(std::size_t a_count) noexcept
	{
		return static_cast<T*>(ni_calloc(a_count, sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* ni_realloc(void* a_ptr, std::size_t a_newSize) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_realloc(T* a_ptr, std::size_t a_newSize) noexcept
	{
		return static_cast<T*>(ni_realloc(static_cast<void*>(a_ptr), a_newSize));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_realloc(T* a_ptr) noexcept
	{
		return static_cast<T*>(ni_realloc(static_cast<void*>(a_ptr), sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* ni_aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* ni_aligned_realloc(T* a_ptr, std::size_t a_newSize = sizeof(T), std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept
	{
		return static_cast<T*>(ni_aligned_realloc(static_cast<void*>(a_ptr), a_newSize, a_alignment));
	}

	__declspec(noalias) void ni_free(void* a_ptr) noexcept;

	template <class T>
	struct NiTMallocInterface
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		NiTMallocInterface() = delete;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static value_type* allocate(size_type a_count) noexcept
		{
			return ni_malloc<value_type>(a_count * sizeof(value_type));
		}

		__declspec(noalias) static void deallocate(value_type* a_ptr) noexcept
		{
			ni_free(static_cast<void*>(a_ptr));
		}
	};
	static_assert(std::is_empty_v<NiTMallocInterface<std::any>>);

	template <class T>
	struct NiTNewInterface
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		NiTNewInterface() = delete;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static value_type* allocate(size_type a_count) //
			noexcept(std::is_nothrow_default_constructible_v<value_type>)
		{
			return new value_type[a_count];
		}

		__declspec(noalias) static void deallocate(value_type* a_ptr) //
			noexcept(std::is_nothrow_destructible_v<value_type>)
		{
			delete[] a_ptr;
		}
	};
	static_assert(std::is_empty_v<NiTNewInterface<std::any>>);

	template <class T>
	struct NiStlAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr NiStlAllocator() noexcept = default;
		constexpr ~NiStlAllocator() noexcept = default;

		constexpr NiStlAllocator(const NiStlAllocator&) noexcept = default;
		constexpr NiStlAllocator(NiStlAllocator&&) noexcept = default;

		constexpr NiStlAllocator& operator=(const NiStlAllocator&) noexcept = default;
		constexpr NiStlAllocator& operator=(NiStlAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = ni_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			ni_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const NiStlAllocator<T1>& a_lhs, [[maybe_unused]] const NiStlAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const NiStlAllocator<T1>& a_lhs, [[maybe_unused]] const NiStlAllocator<T2>& a_rhs) noexcept
	{
		return false;
	}

	template <class T>
	struct NiStlAlignedAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr NiStlAlignedAllocator() noexcept = default;
		constexpr ~NiStlAlignedAllocator() noexcept = default;

		constexpr NiStlAlignedAllocator(const NiStlAlignedAllocator&) noexcept = default;
		constexpr NiStlAlignedAllocator(NiStlAlignedAllocator&&) noexcept = default;

		constexpr NiStlAlignedAllocator& operator=(const NiStlAlignedAllocator&) noexcept = default;
		constexpr NiStlAlignedAllocator& operator=(NiStlAlignedAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = ni_aligned_alloc<value_type>(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			ni_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const NiStlAlignedAllocator<T1>& a_lhs, [[maybe_unused]] const NiStlAlignedAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const NiStlAlignedAllocator<T1>& a_lhs, [[maybe_unused]] const NiStlAlignedAllocator<T2>& a_rhs) noexcept
	{
		return false;
	}
}

#define NI_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size)                                                                \
	{                                                                                                                   \
		auto* mem = RE::ni_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                                              \
	{                                                                                                                   \
		auto* mem = RE::ni_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t a_alignment)                                  \
	{                                                                                                                   \
		auto* mem = RE::ni_aligned_alloc(a_size, a_alignment);                                                          \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t a_alignment)                                \
	{                                                                                                                   \
		auto* mem = RE::ni_aligned_alloc(a_size, a_alignment);                                                          \
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
	void operator delete(void* a_ptr) noexcept { RE::ni_free(a_ptr); }                                                  \
	void operator delete[](void* a_ptr) noexcept { RE::ni_free(a_ptr); }                                                \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::ni_free(a_ptr); }                                \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::ni_free(a_ptr); }                              \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::ni_free(a_ptr); }                                     \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::ni_free(a_ptr); }                                   \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::ni_free(a_ptr); }                   \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::ni_free(a_ptr); }

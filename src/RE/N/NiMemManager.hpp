#pragma once

namespace RE::Impl
{
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto NiMalloc(std::size_t a_size) -> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto NiAlignedAlloc(std::size_t a_size, std::align_val_t a_alignment)
		-> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto NiRealloc(void* a_ptr, std::size_t a_newSize) -> void*;
	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto NiAlignedRealloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment)
		-> void*;
	__declspec(noalias) void NiFree(void* a_ptr);
}

namespace RE
{
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_malloc(std::size_t a_size) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(ni_malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_malloc() noexcept -> T*
	{
		return static_cast<T*>(ni_malloc(sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto ni_aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_aligned_alloc(
		std::size_t a_size = sizeof(T),
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
	{
		return static_cast<T*>(ni_aligned_alloc(a_size, a_alignment));
	}

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(ni_calloc(a_count, sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_realloc(void* a_ptr, std::size_t a_newSize) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_realloc(T* a_ptr, std::size_t a_newSize) noexcept -> T*
	{
		return static_cast<T*>(ni_realloc(static_cast<void*>(a_ptr), a_newSize));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_realloc(T* a_ptr) noexcept -> T*
	{
		return static_cast<T*>(ni_realloc(static_cast<void*>(a_ptr), sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto ni_aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment)
		noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto ni_aligned_realloc(
		T* a_ptr,
		std::size_t a_newSize = sizeof(T),
		std::align_val_t a_alignment = static_cast<std::align_val_t>(alignof(T))) noexcept -> T*
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

		constexpr NiTMallocInterface() noexcept = default;
		constexpr ~NiTMallocInterface() noexcept = default;

		constexpr NiTMallocInterface(const NiTMallocInterface&) noexcept = default;
		constexpr NiTMallocInterface(NiTMallocInterface&&) noexcept = default;

		constexpr auto operator=(const NiTMallocInterface&) noexcept -> NiTMallocInterface& = default;
		constexpr auto operator=(NiTMallocInterface&&) noexcept -> NiTMallocInterface& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) noexcept -> value_type*
		{
			return ni_malloc<value_type>(a_count * sizeof(value_type));
		}

		__declspec(noalias) void deallocate(value_type* a_ptr) noexcept
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

		constexpr NiTNewInterface() noexcept = default;
		constexpr ~NiTNewInterface() noexcept = default;

		constexpr NiTNewInterface(const NiTNewInterface&) noexcept = default;
		constexpr NiTNewInterface(NiTNewInterface&&) noexcept = default;

		constexpr auto operator=(const NiTNewInterface&) noexcept -> NiTNewInterface& = default;
		constexpr auto operator=(NiTNewInterface&&) noexcept -> NiTNewInterface& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count)
			noexcept(std::is_nothrow_default_constructible_v<value_type>) -> value_type*
		{
			return new value_type[a_count];
		}

		__declspec(noalias) void deallocate(value_type* a_ptr) noexcept(std::is_nothrow_destructible_v<value_type>)
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

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NiStlAllocator([[maybe_unused]] const NiStlAllocator<U>& a_other) noexcept
		{
		}

		constexpr NiStlAllocator(const NiStlAllocator&) noexcept = default;
		constexpr NiStlAllocator(NiStlAllocator&&) noexcept = default;

		constexpr auto operator=(const NiStlAllocator&) noexcept -> NiStlAllocator& = default;
		constexpr auto operator=(NiStlAllocator&&) noexcept -> NiStlAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = ni_malloc<value_type>(a_count * sizeof(value_type));
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
			ni_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const NiStlAllocator<T1>& a_lhs,
		[[maybe_unused]] const NiStlAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
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

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NiStlAlignedAllocator([[maybe_unused]] const NiStlAlignedAllocator<U>& a_other) noexcept
		{
		}

		constexpr NiStlAlignedAllocator(const NiStlAlignedAllocator&) noexcept = default;
		constexpr NiStlAlignedAllocator(NiStlAlignedAllocator&&) noexcept = default;

		constexpr auto operator=(const NiStlAlignedAllocator&) noexcept -> NiStlAlignedAllocator& = default;
		constexpr auto operator=(NiStlAlignedAllocator&&) noexcept -> NiStlAlignedAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = ni_aligned_alloc<value_type>(
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
			ni_free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const NiStlAlignedAllocator<T1>& a_lhs,
		[[maybe_unused]] const NiStlAlignedAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}
}

#define NI_HEAP_REDEFINE_NEW(a_type)                                                                                  \
	static_assert(std::is_class_v<a_type>);                                                                           \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size)                                                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = ::RE::ni_malloc(a_size);                                                                          \
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
		auto* mem = ::RE::ni_malloc(a_size);                                                                          \
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
		auto* mem = ::RE::ni_aligned_alloc(a_size, a_alignment);                                                      \
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
		auto* mem = ::RE::ni_aligned_alloc(a_size, a_alignment);                                                      \
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
		return ::RE::ni_malloc(a_size);                                                                               \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                    \
	{                                                                                                                 \
		return ::RE::ni_malloc(a_size);                                                                               \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return ::RE::ni_aligned_alloc(a_size, a_alignment);                                                           \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](                                                                                              \
		std::size_t a_size,                                                                                           \
		std::align_val_t a_alignment,                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return ::RE::ni_aligned_alloc(a_size, a_alignment);                                                           \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t, /*a_size*/, void* a_ptr) noexcept -> void*                               \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t, /*a_size*/, void* a_ptr) noexcept -> void*                             \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t, /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept      \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t, /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept    \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t, /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept   \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t, /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(                                                                                      \
		std::size_t,                                                                                                  \
		/*a_size*/,                                                                                                   \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](                                                                                    \
		std::size_t,                                                                                                  \
		/*a_size*/,                                                                                                   \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr) noexcept                                                                        \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr) noexcept                                                                      \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                      \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                    \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                           \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                         \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t, /*a_size*/, std::align_val_t /*a_alignment*/) noexcept             \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t, /*a_size*/, std::align_val_t /*a_alignment*/) noexcept           \
	{                                                                                                                 \
		::RE::ni_free(a_ptr);                                                                                         \
	}

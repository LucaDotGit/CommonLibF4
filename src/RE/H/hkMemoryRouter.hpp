#pragma once

#include "RE/H/hkLifoAllocator.hpp"

namespace RE
{
	class hkMemoryAllocator;

	class hkMemoryRouter
	{
	public:
		[[nodiscard]]
		static auto GetThreadLocalIndex() noexcept -> std::uint32_t;
		[[nodiscard]]
		static auto GetInstance() noexcept -> hkMemoryRouter*;
		static void SetInstance(hkMemoryRouter* a_router) noexcept;

		// members
		hkLifoAllocator stack;				// 0x00
		hkMemoryAllocator* temp{nullptr};	// 0x50
		hkMemoryAllocator* heap{nullptr};	// 0x58
		hkMemoryAllocator* debug{nullptr};	// 0x60
		hkMemoryAllocator* solver{nullptr}; // 0x68
		void* userData{nullptr};			// 0x70
		std::uint32_t refObjLocalStore{0};	// 0x78
	};

	static_assert(sizeof(hkMemoryRouter) == 0x80);

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_malloc(std::size_t a_size) noexcept -> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_temp_malloc(std::size_t a_size) noexcept -> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_debug_malloc(std::size_t a_size) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_temp_malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_temp_malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_debug_malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_debug_malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_malloc() noexcept -> T*
	{
		return static_cast<T*>(hk_malloc(sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_temp_malloc() noexcept -> T*
	{
		return static_cast<T*>(hk_temp_malloc(sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_debug_malloc() noexcept -> T*
	{
		return static_cast<T*>(hk_debug_malloc(sizeof(T)));
	}

	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_temp_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*;
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_debug_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_calloc(a_count, sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_temp_calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_temp_calloc(a_count, sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_debug_calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_debug_calloc(a_count, sizeof(T)));
	}

	__declspec(noalias) void hk_free(void* a_ptr, std::size_t a_size) noexcept;
	__declspec(noalias) void hk_temp_free(void* a_ptr, std::size_t a_size) noexcept;
	__declspec(noalias) void hk_debug_free(void* a_ptr, std::size_t a_size) noexcept;

	template <class T>
	struct hkStlAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr hkStlAllocator() noexcept = default;
		constexpr ~hkStlAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr hkStlAllocator([[maybe_unused]] const hkStlAllocator<U>& a_other) noexcept
		{
		}

		constexpr hkStlAllocator(const hkStlAllocator&) noexcept = default;
		constexpr hkStlAllocator(hkStlAllocator&&) noexcept = default;

		constexpr auto operator=(const hkStlAllocator&) noexcept -> hkStlAllocator& = default;
		constexpr auto operator=(hkStlAllocator&&) noexcept -> hkStlAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = hk_malloc<value_type>(a_count * sizeof(value_type));
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

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const hkStlAllocator<T1>& a_lhs,
		[[maybe_unused]] const hkStlAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}

	template <class T>
	struct hkStlTempAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::false_type;

		constexpr hkStlTempAllocator() noexcept = default;
		constexpr ~hkStlTempAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr hkStlTempAllocator([[maybe_unused]] const hkStlTempAllocator<U>& a_other) noexcept
		{
		}

		constexpr hkStlTempAllocator(const hkStlTempAllocator&) noexcept = default;
		constexpr hkStlTempAllocator(hkStlTempAllocator&&) noexcept = default;

		constexpr auto operator=(const hkStlTempAllocator&) noexcept -> hkStlTempAllocator& = default;
		constexpr auto operator=(hkStlTempAllocator&&) noexcept -> hkStlTempAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = hk_temp_malloc<value_type>(a_count * sizeof(value_type));
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

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_temp_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const hkStlTempAllocator<T1>& a_lhs,
		[[maybe_unused]] const hkStlTempAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}

	template <class T>
	struct hkStlDebugAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr hkStlDebugAllocator() noexcept = default;
		constexpr ~hkStlDebugAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr hkStlDebugAllocator([[maybe_unused]] const hkStlDebugAllocator<U>& a_other) noexcept
		{
		}

		constexpr hkStlDebugAllocator(const hkStlDebugAllocator&) noexcept = default;
		constexpr hkStlDebugAllocator(hkStlDebugAllocator&&) noexcept = default;

		constexpr auto operator=(const hkStlDebugAllocator&) noexcept -> hkStlDebugAllocator& = default;
		constexpr auto operator=(hkStlDebugAllocator&&) noexcept -> hkStlDebugAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem = hk_debug_malloc<value_type>(a_count * sizeof(value_type));
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

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_debug_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const hkStlDebugAllocator<T1>& a_lhs,
		[[maybe_unused]] const hkStlDebugAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}
}

#define HK_HEAP_REDEFINE_NEW(a_type)                                                                                 \
	static_assert(std::is_class_v<a_type>);                                                                          \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size)                                                                            \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_malloc(a_size);                                                                         \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size)                                                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_malloc(a_size);                                                                         \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, std::align_val_t /*a_alignment*/)                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_malloc(a_size);                                                                         \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, std::align_val_t /*a_alignment*/)                                        \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_malloc(a_size);                                                                         \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                     \
	{                                                                                                                \
		return ::RE::hk_malloc(a_size);                                                                              \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                   \
	{                                                                                                                \
		return ::RE::hk_malloc(a_size);                                                                              \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(                                                                                               \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_malloc(a_size);                                                                              \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](                                                                                             \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_malloc(a_size);                                                                              \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                               \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                             \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept      \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept    \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept   \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(                                                                                     \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](                                                                                   \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr) noexcept                                                                       \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr) noexcept                                                                     \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                     \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                   \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                          \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                        \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept             \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept           \
	{                                                                                                                \
		::RE::hk_free(a_ptr, sizeof(a_type));                                                                        \
	}

#define HK_TEMP_REDEFINE_NEW(a_type)                                                                                 \
	static_assert(std::is_class_v<a_type>);                                                                          \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size)                                                                            \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_temp_malloc(a_size);                                                                    \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size)                                                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_temp_malloc(a_size);                                                                    \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, std::align_val_t /*a_alignment*/)                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_temp_malloc(a_size);                                                                    \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, std::align_val_t /*a_alignment*/)                                        \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_temp_malloc(a_size);                                                                    \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                     \
	{                                                                                                                \
		return ::RE::hk_temp_malloc(a_size);                                                                         \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                   \
	{                                                                                                                \
		return ::RE::hk_temp_malloc(a_size);                                                                         \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(                                                                                               \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_temp_malloc(a_size);                                                                         \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](                                                                                             \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_temp_malloc(a_size);                                                                         \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                               \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                             \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept      \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept    \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept   \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(                                                                                     \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](                                                                                   \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr) noexcept                                                                       \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr) noexcept                                                                     \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                     \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                   \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                          \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                        \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept             \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept           \
	{                                                                                                                \
		::RE::hk_temp_free(a_ptr, sizeof(a_type));                                                                   \
	}

#define HK_DEBUG_REDEFINE_NEW(a_type)                                                                                \
	static_assert(std::is_class_v<a_type>);                                                                          \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size)                                                                            \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_debug_malloc(a_size);                                                                   \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size)                                                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_debug_malloc(a_size);                                                                   \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, std::align_val_t /*a_alignment*/)                                          \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_debug_malloc(a_size);                                                                   \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, std::align_val_t /*a_alignment*/)                                        \
		->void*                                                                                                      \
	{                                                                                                                \
		auto* mem = ::RE::hk_debug_malloc(a_size);                                                                   \
		if (!mem) [[unlikely]] {                                                                                     \
			::REX::Throw<std::bad_alloc>();                                                                          \
		}                                                                                                            \
                                                                                                                     \
		return mem;                                                                                                  \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                     \
	{                                                                                                                \
		return ::RE::hk_debug_malloc(a_size);                                                                        \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                   \
	{                                                                                                                \
		return ::RE::hk_debug_malloc(a_size);                                                                        \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new(                                                                                               \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_debug_malloc(a_size);                                                                        \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	auto operator new[](                                                                                             \
		std::size_t a_size,                                                                                          \
		std::align_val_t /*a_alignment*/,                                                                            \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return ::RE::hk_debug_malloc(a_size);                                                                        \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                               \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                             \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept      \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept    \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept   \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                     \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new(                                                                                     \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	[[nodiscard]]                                                                                                    \
	constexpr auto operator new[](                                                                                   \
		std::size_t /*a_size*/,                                                                                      \
		std::align_val_t /*a_alignment*/,                                                                            \
		void* a_ptr,                                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                       \
	{                                                                                                                \
		return a_ptr;                                                                                                \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr) noexcept                                                                       \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr) noexcept                                                                     \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                     \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                   \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                          \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                        \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept             \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}                                                                                                                \
                                                                                                                     \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept           \
	{                                                                                                                \
		::RE::hk_debug_free(a_ptr, sizeof(a_type));                                                                  \
	}

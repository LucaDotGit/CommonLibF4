#pragma once

#include "RE/H/hkLifoAllocator.hpp"

namespace RE
{
	class hkMemoryAllocator;

	class hkMemoryRouter
	{
	public:
		[[nodiscard]] static hkMemoryRouter* GetInstance();
		static void SetInstance(hkMemoryRouter* a_router);

		// members
		hkLifoAllocator stack;				  // 00
		hkMemoryAllocator* temp{ nullptr };	  // 50
		hkMemoryAllocator* heap{ nullptr };	  // 58
		hkMemoryAllocator* debug{ nullptr };  // 60
		hkMemoryAllocator* solver{ nullptr }; // 68
		void* userData{ nullptr };			  // 70
		std::uint32_t refObjLocalStore{ 0 };  // 78
	};
	static_assert(sizeof(hkMemoryRouter) == 0x80);

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_malloc(std::size_t a_size) noexcept;
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_temp_malloc(std::size_t a_size) noexcept;
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_debug_malloc(std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(hk_malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_temp_malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(hk_temp_malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_debug_malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(hk_debug_malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_malloc() noexcept
	{
		return static_cast<T*>(hk_malloc(sizeof(T)));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_temp_malloc() noexcept
	{
		return static_cast<T*>(hk_temp_malloc(sizeof(T)));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_debug_malloc() noexcept
	{
		return static_cast<T*>(hk_debug_malloc(sizeof(T)));
	}

	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_calloc(std::size_t a_count, std::size_t a_size) noexcept;
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_temp_calloc(std::size_t a_count, std::size_t a_size) noexcept;
	[[nodiscard]] __declspec(allocator) __declspec(restrict) void* hk_debug_calloc(std::size_t a_count, std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_calloc(std::size_t a_count) noexcept
	{
		return static_cast<T*>(hk_calloc(a_count, sizeof(T)));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_temp_calloc(std::size_t a_count) noexcept
	{
		return static_cast<T*>(hk_temp_calloc(a_count, sizeof(T)));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_debug_calloc(std::size_t a_count) noexcept
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

		constexpr hkStlAllocator(const hkStlAllocator&) noexcept = default;
		constexpr hkStlAllocator(hkStlAllocator&&) noexcept = default;

		constexpr hkStlAllocator& operator=(const hkStlAllocator&) noexcept = default;
		constexpr hkStlAllocator& operator=(hkStlAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = hk_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const hkStlAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const hkStlAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlAllocator<T2>& a_rhs) noexcept
	{
		return false;
	}

	template <class T>
	struct hkStlTempAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr hkStlTempAllocator() noexcept = default;
		constexpr ~hkStlTempAllocator() noexcept = default;

		constexpr hkStlTempAllocator(const hkStlTempAllocator&) noexcept = default;
		constexpr hkStlTempAllocator(hkStlTempAllocator&&) noexcept = default;

		constexpr hkStlTempAllocator& operator=(const hkStlTempAllocator&) noexcept = default;
		constexpr hkStlTempAllocator& operator=(hkStlTempAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = hk_temp_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_temp_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const hkStlTempAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlTempAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const hkStlTempAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlTempAllocator<T2>& a_rhs) noexcept
	{
		return false;
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

		constexpr hkStlDebugAllocator(const hkStlDebugAllocator&) noexcept = default;
		constexpr hkStlDebugAllocator(hkStlDebugAllocator&&) noexcept = default;

		constexpr hkStlDebugAllocator& operator=(const hkStlDebugAllocator&) noexcept = default;
		constexpr hkStlDebugAllocator& operator=(hkStlDebugAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(size_type a_count)
		{
			auto* mem = hk_debug_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				throw std::bad_alloc();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, size_type a_count) noexcept
		{
			hk_debug_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==([[maybe_unused]] const hkStlDebugAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlDebugAllocator<T2>& a_rhs) noexcept
	{
		return true;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=([[maybe_unused]] const hkStlDebugAllocator<T1>& a_lhs, [[maybe_unused]] const hkStlDebugAllocator<T2>& a_rhs) noexcept
	{
		return false;
	}
}

#define HK_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size)                                                                \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                                              \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t)                                              \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t)                                            \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
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
	void operator delete(void* a_ptr) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }                                  \
	void operator delete[](void* a_ptr) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }                                \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }                \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }              \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }                     \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }                   \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }   \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_free(a_ptr, sizeof(a_type)); }

#define HK_TEMP_REDEFINE_NEW(a_type)                                                                                       \
	static_assert(std::is_class_v<a_type>);                                                                                \
                                                                                                                           \
	[[nodiscard]] void* operator new(std::size_t a_size)                                                                   \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			throw std::bad_alloc();                                                                                        \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                                                 \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			throw std::bad_alloc();                                                                                        \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t)                                                 \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			throw std::bad_alloc();                                                                                        \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t)                                               \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			throw std::bad_alloc();                                                                                        \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                        \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                      \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }      \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }    \
                                                                                                                           \
	void operator delete(void* a_ptr) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }                                \
	void operator delete[](void* a_ptr) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }                              \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }              \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }            \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }                   \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }                 \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); } \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_temp_free(a_ptr, sizeof(a_type)); }

#define HK_DEBUG_REDEFINE_NEW(a_type)                                                                                       \
	static_assert(std::is_class_v<a_type>);                                                                                 \
                                                                                                                            \
	[[nodiscard]] void* operator new(std::size_t a_size)                                                                    \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			throw std::bad_alloc();                                                                                         \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                                                  \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			throw std::bad_alloc();                                                                                         \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t)                                                  \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			throw std::bad_alloc();                                                                                         \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t)                                                \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			throw std::bad_alloc();                                                                                         \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                         \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                       \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }       \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }     \
                                                                                                                            \
	void operator delete(void* a_ptr) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }                                \
	void operator delete[](void* a_ptr) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }                              \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }              \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }            \
	void operator delete(void* a_ptr, std::size_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }                   \
	void operator delete[](void* a_ptr, std::size_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }                 \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); } \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { RE::hk_debug_free(a_ptr, sizeof(a_type)); }

#pragma once

#include "RE/H/hkLifoAllocator.hpp"

namespace RE
{
	class hkMemoryAllocator;

	class hkMemoryRouter
	{
	public:
		using Allocator = hkMemoryAllocator;
		using Stack = hkLifoAllocator;

		[[nodiscard]] static hkMemoryRouter* GetInstance();
		static void SetInstance(hkMemoryRouter* a_router);

		// members
		Stack stack;						 // 00
		Allocator* temp{ nullptr };			 // 50
		Allocator* heap{ nullptr };			 // 58
		Allocator* debug{ nullptr };		 // 60
		Allocator* solver{ nullptr };		 // 68
		void* userData{ nullptr };			 // 70
		std::uint32_t refObjLocalStore{ 0 }; // 78
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
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = hk_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, std::size_t a_count) noexcept
		{
			hk_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T>
	struct hkStlTempAllocator
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = hk_temp_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, std::size_t a_count) noexcept
		{
			hk_temp_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};

	template <class T>
	struct hkStlDebugAllocator
		: public std::allocator<T>
	{
	public:
		using value_type = T;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) value_type* allocate(std::size_t a_count) noexcept
		{
			auto* mem = hk_debug_malloc<value_type>(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, std::size_t a_count) noexcept
		{
			hk_debug_free(static_cast<void*>(a_ptr), a_count * sizeof(value_type));
		}
	};
}

#define HK_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                                                       \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                                                     \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t) noexcept                                     \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                        \
			REX::AllocationFail();                                                                                      \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t) noexcept                                   \
	{                                                                                                                   \
		auto* mem = RE::hk_malloc(a_size);                                                                              \
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
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                                                          \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			REX::AllocationFail();                                                                                         \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                                                        \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			REX::AllocationFail();                                                                                         \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t) noexcept                                        \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			REX::AllocationFail();                                                                                         \
		}                                                                                                                  \
                                                                                                                           \
		return mem;                                                                                                        \
	}                                                                                                                      \
                                                                                                                           \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t) noexcept                                      \
	{                                                                                                                      \
		auto* mem = RE::hk_temp_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                           \
			REX::AllocationFail();                                                                                         \
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
	[[nodiscard]] void* operator new(std::size_t a_size) noexcept                                                           \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			REX::AllocationFail();                                                                                          \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new[](std::size_t a_size) noexcept                                                         \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			REX::AllocationFail();                                                                                          \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t) noexcept                                         \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			REX::AllocationFail();                                                                                          \
		}                                                                                                                   \
                                                                                                                            \
		return mem;                                                                                                         \
	}                                                                                                                       \
                                                                                                                            \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t) noexcept                                       \
	{                                                                                                                       \
		auto* mem = RE::hk_debug_malloc(a_size);                                                                            \
		if (!mem) [[unlikely]] {                                                                                            \
			REX::AllocationFail();                                                                                          \
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

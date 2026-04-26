#pragma once

#include "RE/H/hkMemoryAllocator.hpp"

namespace RE
{
	class hkContainerTempAllocator
	{
	public:
		class __declspec(novtable) Allocator
			: public hkMemoryAllocator // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::hkContainerTempAllocator__Allocator };
			inline static constexpr auto VTABLE{ VTABLE::hkContainerTempAllocator__Allocator };
		};
		static_assert(sizeof(Allocator) == 0x08);

		[[nodiscard]] static Allocator& GetAllocator();
	};
	static_assert(std::is_empty_v<hkContainerTempAllocator>);

	__declspec(allocator) __declspec(restrict) void* hk_container_temp_malloc(std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_container_temp_malloc(std::size_t a_size) noexcept
	{
		return static_cast<T*>(hk_container_temp_malloc(a_size));
	}

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_container_temp_malloc() noexcept
	{
		return static_cast<T*>(hk_container_temp_malloc(sizeof(T)));
	}

	__declspec(allocator) __declspec(restrict) void* hk_container_temp_calloc(std::size_t a_count, std::size_t a_size) noexcept;

	template <class T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* hk_container_temp_calloc(std::size_t a_count) noexcept
	{
		return static_cast<T*>(hk_container_temp_calloc(a_count, sizeof(T)));
	}

	__declspec(noalias) void hk_container_temp_free(void* a_ptr, std::size_t a_size) noexcept;
}

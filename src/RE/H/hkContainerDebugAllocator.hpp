#pragma once

#include "RE/H/hkMemoryAllocator.hpp"

namespace RE
{
	class hkContainerDebugAllocator
	{
	public:
		class __declspec(novtable) Allocator : public hkMemoryAllocator // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::hkContainerDebugAllocator__Allocator;
			inline static constexpr const auto& VTABLE = VTABLE::hkContainerDebugAllocator__Allocator;
		};

		static_assert(sizeof(Allocator) == 0x08);

		[[nodiscard]]
		static auto GetAllocator() noexcept -> Allocator&;
	};

	static_assert(std::is_empty_v<hkContainerDebugAllocator>);

	__declspec(allocator) __declspec(restrict) auto hk_container_debug_malloc(std::size_t a_size) noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_container_debug_malloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_container_debug_malloc(a_count * sizeof(T)));
	}

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_container_debug_malloc() noexcept -> T*
	{
		return static_cast<T*>(hk_container_debug_malloc(sizeof(T)));
	}

	__declspec(allocator) __declspec(restrict) auto hk_container_debug_calloc(std::size_t a_count, std::size_t a_size)
		noexcept -> void*;

	template <class T>
	[[nodiscard]]
	__declspec(allocator) __declspec(restrict) auto hk_container_debug_calloc(std::size_t a_count) noexcept -> T*
	{
		return static_cast<T*>(hk_container_debug_calloc(a_count, sizeof(T)));
	}

	__declspec(noalias) void hk_container_debug_free(void* a_ptr, std::size_t a_size) noexcept;
}

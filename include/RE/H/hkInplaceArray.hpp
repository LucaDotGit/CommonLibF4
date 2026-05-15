#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArray
		: public hkArray<T, Allocator>
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		// members
		std::array<T, N> storage; // 10
	};
	static_assert(sizeof(hkInplaceArray<std::byte, 32>) == 0x30);

	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArrayAligned16
		: public hkArray<T, Allocator>
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		// members
		std::array<std::byte, 0x20 - 0x10> pad10;	  // 10
		std::array<std::byte, sizeof(T) * N> storage; // 20
	};
	static_assert(sizeof(hkInplaceArrayAligned16<std::uintptr_t, 24>) == 0xE0);
}

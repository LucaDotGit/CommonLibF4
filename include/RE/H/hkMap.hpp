#pragma once

#include "RE/H/hkContainerHeapAllocator.hpp"

namespace RE
{
	template <class T>
	class hkMapOperations
	{
	public:
	};
	static_assert(std::is_empty_v<hkMapOperations<std::any>>);

	template <class T, class U, class Operations = hkMapOperations<T>, class Allocator = hkContainerHeapAllocator>
	class hkMap
	{
	public:
		class Pair
		{
		public:
			// members
			T key; // 00
			U val; // ??
		};

		// members
		Pair* element;		   // 00
		std::int32_t numElems; // 08
		std::int32_t hashMod;  // 0C
	};
	static_assert(sizeof(hkMap<std::any, std::any>) == 0x10);

	template <class T, class U, class Allocator = hkContainerHeapAllocator>
	class hkPointerMap
	{
	public:
		// members
		hkMap<std::uint64_t, std::uint64_t, hkMapOperations<std::uint64_t>, Allocator> map; // 10
	};
	static_assert(sizeof(hkPointerMap<void*, void*>) == 0x10);
}

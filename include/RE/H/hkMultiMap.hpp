#pragma once

#include "RE/H/hkContainerHeapAllocator.hpp"

namespace RE
{
	template <class T>
	class hkMultiMapOperations
	{
	public:
	};
	static_assert(std::is_empty_v<hkMultiMapOperations<std::any>>);

	template <class T, class U, class Operations = hkMultiMapOperations<T>, class Allocator = hkContainerHeapAllocator>
	class hkMultiMap
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
		Pair* _elems;			// 00
		std::int32_t _numElems; // 08
		std::int32_t _hashMod;	// 0C
	};
	static_assert(sizeof(hkMultiMap<std::any, std::any>) == 0x10);
}

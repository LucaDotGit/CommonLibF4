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
			T key; // 0x00
			U val; // 0x??
		};

		// members
		Pair* _elems;			// 0x00
		std::int32_t _numElems; // 0x08
		std::int32_t _hashMod;	// 0x0C
	};

	static_assert(sizeof(hkMultiMap<std::any, std::any>) == 0x10);
}

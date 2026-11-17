#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hkDefaultFreeListArrayOperations
	{
	public:
	};

	template <class T>
	class hkFreeListArrayElement
	{
	public:
		// members
		T pod; // 0x00
	};

	template <class T, class I, std::int32_t G, class O = hkDefaultFreeListArrayOperations<T>>
	class hkFreeListArray
	{
	public:
		// members
		hkArray<hkFreeListArrayElement<T>> elements; // 0x00
		std::int32_t firstFree;						 // 0x??
	};

	static_assert(sizeof(hkFreeListArray<std::uint8_t, std::uint8_t, 0>) == 0x18);
}

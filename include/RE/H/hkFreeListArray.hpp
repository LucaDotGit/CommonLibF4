#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hkDefaultFreeListArrayOperations
	{
	public:
		static std::uint32_t GetNext(const T& a_element)
		{
			return reinterpret_cast<const std::uint32_t&>(a_element);
		}

		static void SetEmpty(T& a_element, std::uint32_t a_next)
		{
			reinterpret_cast<std::uint32_t&>(a_element) = a_next;
		}
	};

	template <class T>
	class hkFreeListArrayElement
	{
	public:
		// members
		T pod; // 00
	};

	template <class T, class I, std::int32_t G, class O = hkDefaultFreeListArrayOperations<T>>
	class hkFreeListArray
	{
	public:
		// members
		hkArray<hkFreeListArrayElement<T>> _elements; // 00
		std::int32_t firstFree;						  // ??
	};
	static_assert(sizeof(hkFreeListArray<std::uint8_t, std::uint8_t, 0>) == 0x18);
}

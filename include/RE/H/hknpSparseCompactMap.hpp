#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hknpSparseCompactMap
	{
	public:
		std::uint32_t secondaryKeyMask;	  // 00
		std::uint32_t sencondaryKeyBits;  // 04
		hkArray<T> primaryKeyToIndex;	  // 08
		hkArray<T> valueAndSecondaryKeys; // 18
	};
	static_assert(sizeof(hknpSparseCompactMap<std::uint16_t>) == 0x28);
}

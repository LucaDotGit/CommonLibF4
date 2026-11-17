#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hknpSparseCompactMap
	{
	public:
		std::uint32_t secondaryKeyMask;	  // 0x00
		std::uint32_t sencondaryKeyBits;  // 0x04
		hkArray<T> primaryKeyToIndex;	  // 0x08
		hkArray<T> valueAndSecondaryKeys; // 0x18
	};

	static_assert(sizeof(hknpSparseCompactMap<std::uint16_t>) == 0x28);
}

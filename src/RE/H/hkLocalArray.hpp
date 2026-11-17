#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hkLocalArray : public hkArray<T>
	{
	public:
		// members
		T* localMemory;				  // 0x10
		std::int32_t initialCapacity; // 0x18
	};

	static_assert(sizeof(hkLocalArray<std::any>) == 0x20);
}

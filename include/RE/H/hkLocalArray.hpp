#pragma once

#include "RE/H/hkArray.hpp"

namespace RE
{
	template <class T>
	class hkLocalArray
		: public hkArray<T>
	{
	public:
		// members
		T* localMemory;				  // 10
		std::int32_t initialCapacity; // 18
	};
	static_assert(sizeof(hkLocalArray<std::any>) == 0x20);
}

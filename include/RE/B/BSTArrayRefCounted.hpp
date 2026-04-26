#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	template <class T, class Allocator = BSTArrayHeapAllocator>
	class BSTArrayRefCounted
		: public BSTArray<NiPointer<T>, Allocator>
	{
	public:
		// members
		volatile std::uint32_t refCount; // ??
	};
}

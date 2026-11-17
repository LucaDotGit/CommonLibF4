#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	template <class T, class Allocator = BSTArrayHeapAllocator>
	class BSTArrayRefCounted :
		public BSTArray<NiPointer<T>, Allocator>, // 0x00
		public BSIntrusiveRefCounted			  // 0x18
	{
	public:
	};
}

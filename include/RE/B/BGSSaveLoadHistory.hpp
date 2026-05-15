#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSSaveLoadHistory
	{
	public:
		// members
		BSTArray<char*, BSTArrayHeapAllocator> notes; // 00
	};
	static_assert(sizeof(BGSSaveLoadHistory) == 0x18);
}

#pragma once

#include "RE/B/BGSChangeFlags.hpp"
#include "RE/B/BGSUnloadedFormBuffer.hpp"

namespace RE
{
	class BGSFormChanges
	{
	public:
		// members
		BGSChangeFlags changeFlags;				  // 00
		BGSUnloadedFormBuffer unloadedFormBuffer; // 08
	};
	static_assert(sizeof(BGSFormChanges) == 0x10);
}

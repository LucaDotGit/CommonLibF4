#pragma once

#include "RE/B/BGSSaveLoadBuffer.hpp"

namespace RE
{
	class BGSUnloadedFormBuffer
	{
	public:
		// members
		BGSSaveLoadBuffer buffer; // 00
	};
	static_assert(sizeof(BGSUnloadedFormBuffer) == 0x08);
}

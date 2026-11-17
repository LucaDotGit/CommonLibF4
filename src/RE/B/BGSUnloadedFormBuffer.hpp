#pragma once

#include "RE/B/BGSSaveLoadBuffer.hpp"

namespace RE
{
	class BGSUnloadedFormBuffer
	{
	public:
		// members
		BGSSaveLoadBuffer buffer; // 0x00
	};

	static_assert(sizeof(BGSUnloadedFormBuffer) == 0x08);
}

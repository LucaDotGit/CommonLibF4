#pragma once

#include "RE/B/BGSSaveLoadBuffer.hpp"

namespace RE
{
	class BGSLoadGameSubBuffer
	{
	public:
		// members
		BGSSaveLoadBuffer buffer; // 0x00
	};

	static_assert(sizeof(BGSLoadGameSubBuffer) == 0x08);
}

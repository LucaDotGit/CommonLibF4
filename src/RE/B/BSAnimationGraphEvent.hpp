#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class BSAnimationGraphEvent
	{
	public:
		// members
		std::uint64_t holderID; // 0x00
		BSFixedString tag;		// 0x08
		BSFixedString payload;	// 0x10
	};

	static_assert(sizeof(BSAnimationGraphEvent) == 0x18);
}

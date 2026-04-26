#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class BSAnimationGraphEvent
	{
	public:
		// members
		std::uint64_t holderID; // 00
		BSFixedString tag;		// 08
		BSFixedString payload;	// 10
	};
	static_assert(sizeof(BSAnimationGraphEvent) == 0x18);
}

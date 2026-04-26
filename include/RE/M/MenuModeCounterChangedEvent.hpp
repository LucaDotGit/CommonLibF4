#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class MenuModeCounterChangedEvent
	{
	public:
		// members
		BSFixedString menuName; // 00
		bool incrementing;		// 08
	};
	static_assert(sizeof(MenuModeCounterChangedEvent) == 0x10);
}

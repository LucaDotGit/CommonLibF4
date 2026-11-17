#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class MenuModeCounterChangedEvent
	{
	public:
		// members
		BSFixedString menuName; // 0x00
		bool incrementing;		// 0x08
	};

	static_assert(sizeof(MenuModeCounterChangedEvent) == 0x10);
}

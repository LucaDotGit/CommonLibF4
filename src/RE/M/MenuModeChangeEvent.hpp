#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class MenuModeChangeEvent
	{
	public:
		// members
		BSFixedString menuName; // 0x00
		bool enteringMenuMode;	// 0x08
	};

	static_assert(sizeof(MenuModeChangeEvent) == 0x10);
}

#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class MenuOpenCloseEvent
	{
	public:
		// members
		BSFixedString menuName; // 0x00
		bool opening;			// 0x08
	};

	static_assert(sizeof(MenuOpenCloseEvent) == 0x10);
}

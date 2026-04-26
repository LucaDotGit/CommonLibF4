#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/S/ShowHUDMessageEvent.hpp"

namespace RE
{
	class HUDMessageDisplayDataEvent
		: public BSTValueEvent<ShowHUDMessageEvent> // 0
	{
	public:
	};
	static_assert(sizeof(HUDMessageDisplayDataEvent) == 0x20);
}

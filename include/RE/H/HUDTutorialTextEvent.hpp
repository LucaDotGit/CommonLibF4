#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class HUDTutorialTextEvent
		: public BSTValueEvent<BSFixedString> // 00
	{
	public:
	};
	static_assert(sizeof(HUDTutorialTextEvent) == 0x10);
}

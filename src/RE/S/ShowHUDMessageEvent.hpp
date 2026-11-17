#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class ShowHUDMessageEvent
	{
	public:
		// members
		BSFixedString messageText; // 0x00
		BSFixedString soundName;   // 0x08
		bool canBeThrottled;	   // 0x10
		bool isWarningMessage;	   // 0x11
		bool isRadioMessage;	   // 0x12
	};

	static_assert(sizeof(ShowHUDMessageEvent) == 0x18);
}

#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class ShowHUDMessageEvent
	{
	public:
		// members
		BSFixedString MessageText; // 00
		BSFixedString SoundName;   // 08
		bool CanBeThrottled;	   // 10
		bool IsWarningMessage;	   // 11
		bool IsRadioMessage;	   // 12
	};
	static_assert(sizeof(ShowHUDMessageEvent) == 0x18);
}

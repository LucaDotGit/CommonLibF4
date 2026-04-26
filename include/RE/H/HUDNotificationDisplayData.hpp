#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDNotificationDisplayData
	{
	public:
		// members
		BSFixedStringCS prefixText;	 // 00
		BSFixedStringCS messageText; // 08
	};
	static_assert(sizeof(HUDNotificationDisplayData) == 0x10);
}

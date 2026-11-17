#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDNotificationDisplayData
	{
	public:
		// members
		BSFixedStringCS prefixText;	 // 0x00
		BSFixedStringCS messageText; // 0x08
	};

	static_assert(sizeof(HUDNotificationDisplayData) == 0x10);
}

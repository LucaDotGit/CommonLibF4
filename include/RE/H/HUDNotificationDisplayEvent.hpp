#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDNotificationDisplayData.hpp"

namespace RE
{
	class HUDNotificationDisplayEvent
		: public BSTValueEvent<HUDNotificationDisplayData> // 00
	{
	public:
	};
	static_assert(sizeof(HUDNotificationDisplayEvent) == 0x18);
}

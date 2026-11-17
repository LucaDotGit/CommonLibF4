#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/X/XPChangeData.hpp"

namespace RE
{
	class HUDExperienceUpdateEvent : public BSTValueEvent<XPChangeData> // 0x00
	{
	public:
	};

	static_assert(sizeof(HUDExperienceUpdateEvent) == 0x14);
}

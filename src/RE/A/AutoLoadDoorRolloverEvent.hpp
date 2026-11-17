#pragma once

#include "RE/A/AutoLoadDoorRolloverData.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class AutoLoadDoorRolloverEvent : public BSTValueEvent<AutoLoadDoorRolloverData> // 0x00
	{
	public:
	};

	static_assert(sizeof(AutoLoadDoorRolloverEvent) == 0x18);
}

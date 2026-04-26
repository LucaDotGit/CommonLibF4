#pragma once

#include "RE/A/AutoLoadDoorRolloverData.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class AutoLoadDoorRolloverEvent
		: public BSTValueEvent<AutoLoadDoorRolloverData> // 00
	{
	public:
	};
	static_assert(sizeof(AutoLoadDoorRolloverEvent) == 0x18);
}

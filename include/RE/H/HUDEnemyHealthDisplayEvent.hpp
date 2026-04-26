#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDEnemyHealthDisplayData.hpp"

namespace RE
{
	class HUDEnemyHealthDisplayEvent
		: public BSTValueEvent<HUDEnemyHealthDisplayData> // 00
	{
	public:
	};
	static_assert(sizeof(HUDEnemyHealthDisplayEvent) == 0x20);
}

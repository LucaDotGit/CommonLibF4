#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/nsStatsMenuUtils_ConditionBoyFunctor.hpp"

namespace RE
{
	class ConditionBoyEvent
		: public BSTValueEvent<nsStatsMenuUtils::ConditionBoyFunctor> // 00
	{
	public:
	};
	static_assert(sizeof(ConditionBoyEvent) == 0x0C);
}

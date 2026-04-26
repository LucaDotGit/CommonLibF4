#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/nsHUDTypes_ObjectiveData.hpp"

namespace RE
{
	class HUDObjectiveDisplayEvent
		: public BSTValueEvent<nsHUDTypes::ObjectiveData> // 00
	{
	public:
	};
	static_assert(sizeof(HUDObjectiveDisplayEvent) == 0x18);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PickRefStateChangedEvent
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(PickRefStateChangedEvent) == 0x02);
}

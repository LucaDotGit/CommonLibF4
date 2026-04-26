#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class RolloverSuppressedEvent
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(RolloverSuppressedEvent) == 0x02);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class InventoryUpdateEvent
		: public BSTValueEvent<ObjectRefHandle> // 00
	{
	public:
	};
	static_assert(sizeof(InventoryUpdateEvent) == 0x08);
}

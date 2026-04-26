#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE::InventoryInterface
{
	class Handle;
}

namespace RE::BGSInventoryItemEvent
{
	class Event
	{
	public:
		// members
		ObjectRefHandle ownerRef;		  // 00
		InventoryInterface::Handle* item; // 04
	};
	static_assert(sizeof(Event) == 0x10);
}

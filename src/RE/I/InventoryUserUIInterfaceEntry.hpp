#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/I/InventoryInterface_Handle.hpp"

namespace RE
{
	class InventoryUserUIInterfaceEntry
	{
	public:
		// members
		InventoryInterface::Handle invHandle;		// 0x00
		BSTSmallArray<std::uint16_t, 4> stackIndex; // 0x08
	};

	static_assert(sizeof(InventoryUserUIInterfaceEntry) == 0x20);
}

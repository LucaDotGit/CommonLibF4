#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/I/InventoryUserUIInterfaceEntry.hpp"

namespace RE
{
	class InvInterfaceStateChangeEvent;

	class __declspec(novtable) InventoryUserUIInterface : public BSTEventSource<InvInterfaceStateChangeEvent> // 0x00
	{
	public:
		// members
		ObjectRefHandle inventoryRef;							// 0x58
		BSTArray<InventoryUserUIInterfaceEntry> stackedEntries; // 0x60
		bool entriesInvalid;									// 0x78
	};

	static_assert(sizeof(InventoryUserUIInterface) == 0x80);
}

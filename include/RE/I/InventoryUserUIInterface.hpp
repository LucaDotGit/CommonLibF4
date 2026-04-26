#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/I/InventoryUserUIInterfaceEntry.hpp"

namespace RE
{
	class InvInterfaceStateChangeEvent;

	class __declspec(novtable) InventoryUserUIInterface
		: public BSTEventSource<InvInterfaceStateChangeEvent> // 00
	{
	public:
		// members
		ObjectRefHandle inventoryRef;							// 58
		BSTArray<InventoryUserUIInterfaceEntry> stackedEntries; // 60
		bool entriesInvalid;									// 78
	};
	static_assert(sizeof(InventoryUserUIInterface) == 0x80);
}

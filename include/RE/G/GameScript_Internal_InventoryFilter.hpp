#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::GameScript
{
	class InventoryFilter
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTSet<TESFormID> filters; // 08
	};
	static_assert(sizeof(InventoryFilter) == 0x38);
}

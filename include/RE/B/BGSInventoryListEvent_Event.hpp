#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE::BGSInventoryListEvent
{
	class Event
	{
	public:
		enum class EventType : std::int16_t
		{
			kAddStack = 0,
			kChangedStack = 1,
			kAddNewItem = 2,
			kRemoveItem = 3,
			kClear = 4,
			UpdateWeight = 5
		};

		// members
		REX::Enum<EventType, std::int16_t> eventType; // 00
		ObjectRefHandle ownerRef;					  // 04
		TESBoundObject* objectAffected;				  // 08
		std::uint32_t count;						  // 10
		std::uint32_t stackID;						  // 14
	};
	static_assert(sizeof(Event) == 0x18);
}

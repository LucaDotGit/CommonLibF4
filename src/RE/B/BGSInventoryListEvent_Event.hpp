#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE::BGSInventoryListEvent
{
	class Event
	{
	public:
		enum class EventType : std::int16_t
		{
			AddStack = 0,
			ChangedStack = 1,
			AddNewItem = 2,
			RemoveItem = 3,
			Clear = 4,
			UpdateWeight = 5
		};

		// members
		REX::Enum<EventType, std::int16_t> eventType; // 0x00
		ObjectRefHandle ownerRef;					  // 0x04
		TESBoundObject* objectAffected;				  // 0x08
		std::uint32_t count;						  // 0x10
		std::uint32_t stackID;						  // 0x14
	};

	static_assert(sizeof(Event) == 0x18);
}

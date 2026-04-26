#pragma once

#include "RE/B/BSFixedString.hpp"
namespace RE
{
	class HUDInventoryChangeMessageEvent
	{
	public:
		enum class ItemChangeType : std::int32_t
		{
			kAdded = 0,
			kRemoved = 1
		};

		// members
		TESBoundObject* boundObject;						// 00
		BSFixedStringCS fullDisplayName;					// 08
		std::uint32_t count;								// 10
		REX::Enum<ItemChangeType, std::int32_t> changeType; // 14
	};
	static_assert(sizeof(HUDInventoryChangeMessageEvent) == 0x18);
}

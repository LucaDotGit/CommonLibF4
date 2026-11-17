#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDInventoryChangeMessageEvent
	{
	public:
		enum class ItemChangeType : std::int32_t
		{
			Added = 0,
			Removed = 1
		};

		// members
		TESBoundObject* boundObject;						// 0x00
		BSFixedStringCS fullDisplayName;					// 0x08
		std::uint32_t count;								// 0x10
		REX::Enum<ItemChangeType, std::int32_t> changeType; // 0x14
	};

	static_assert(sizeof(HUDInventoryChangeMessageEvent) == 0x18);
}

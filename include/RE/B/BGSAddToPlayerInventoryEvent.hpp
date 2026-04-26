#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class ACQUIRE_TYPE : std::int32_t;

	class BGSAddToPlayerInventoryEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSAddToPlayerInventoryEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle ownerRef;						   // 00
		ObjectRefHandle containerRef;					   // 04
		BGSLocation* location;							   // 08
		TESForm* baseItem;								   // 10
		REX::Enum<ACQUIRE_TYPE, std::int32_t> acquireType; // 18
		std::uint32_t itemCount;						   // 1C
	};
	static_assert(sizeof(BGSAddToPlayerInventoryEvent) == 0x20);
}

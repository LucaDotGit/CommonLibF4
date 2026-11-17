#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class ACQUIRE_TYPE : std::int32_t;

	class BGSAddToPlayerInventoryEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX =
				REL::Relocation<std::uint32_t*>{ID::BGSAddToPlayerInventoryEvent::EventIndex};
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle ownerRef;						   // 0x00
		ObjectRefHandle containerRef;					   // 0x04
		BGSLocation* location;							   // 0x08
		TESForm* baseItem;								   // 0x10
		REX::Enum<ACQUIRE_TYPE, std::int32_t> acquireType; // 0x18
		std::uint32_t itemCount;						   // 0x1C
	};

	static_assert(sizeof(BGSAddToPlayerInventoryEvent) == 0x20);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCraftItemEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSCraftItemEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle workbenchRef; // 0x00
		BGSLocation* location;		  // 0x08
		TESForm* createdBaseItem;	  // 0x10
	};

	static_assert(sizeof(BGSCraftItemEvent) == 0x18);
}

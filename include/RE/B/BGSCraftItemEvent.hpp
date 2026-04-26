#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCraftItemEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSCraftItemEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle workbenchRef; // 00
		BGSLocation* location;		  // 08
		TESForm* createdBaseItem;	  // 10
	};
	static_assert(sizeof(BGSCraftItemEvent) == 0x18);
}

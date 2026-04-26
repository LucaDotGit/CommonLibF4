#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSBribeNPCEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSBribeNPCEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 00
		std::uint32_t goldAmount; // 04
	};
	static_assert(sizeof(BGSBribeNPCEvent) == 0x08);
}

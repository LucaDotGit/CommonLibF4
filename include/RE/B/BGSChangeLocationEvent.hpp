#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSChangeLocationEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSChangeLocationEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 00
		BGSLocation* oldLocation; // 08
		BGSLocation* newLocation; // 10
	};
	static_assert(sizeof(BGSChangeLocationEvent) == 0x18);
}

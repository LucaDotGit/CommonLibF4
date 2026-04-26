#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSDiscoverDeadBodyEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSDiscoverDeadBodyEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;	  // 00
		ObjectRefHandle deadActorRef; // 04
		BGSLocation* location;		  // 08
	};
	static_assert(sizeof(BGSDiscoverDeadBodyEvent) == 0x10);
}

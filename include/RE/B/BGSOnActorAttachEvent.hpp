#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSOnActorAttachEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSOnActorAttachEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;	  // 00
		ObjectRefHandle actorRef; // 08
	};
	static_assert(sizeof(BGSOnActorAttachEvent) == 0x10);
}

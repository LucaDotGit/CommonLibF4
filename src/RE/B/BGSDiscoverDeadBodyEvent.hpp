#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSDiscoverDeadBodyEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSDiscoverDeadBodyEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;	  // 0x00
		ObjectRefHandle deadActorRef; // 0x04
		BGSLocation* location;		  // 0x08
	};

	static_assert(sizeof(BGSDiscoverDeadBodyEvent) == 0x10);
}

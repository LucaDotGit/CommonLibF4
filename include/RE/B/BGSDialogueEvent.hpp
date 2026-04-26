#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSDialogueEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSDialogueEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;		// 00
		ObjectRefHandle actorRef01; // 08
		ObjectRefHandle actorRef02; // 0C
	};
	static_assert(sizeof(BGSDialogueEvent) == 0x10);
}

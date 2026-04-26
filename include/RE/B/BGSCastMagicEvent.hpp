#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCastMagicEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSCastMagicEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle castingActorRef; // 00
		ObjectRefHandle spellTargetRef;	 // 04
		BGSLocation* location;			 // 08
		std::uint32_t crimeType;		 // 10
	};
	static_assert(sizeof(BGSCastMagicEvent) == 0x18);
}

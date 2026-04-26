#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSInfectionEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSInfectionEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle transmittingActorRef; // 00
		TESForm* infection;					  // 04
	};
	static_assert(sizeof(BGSInfectionEvent) == 0x10);
}

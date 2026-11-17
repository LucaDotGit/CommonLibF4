#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSInfectionEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSInfectionEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle transmittingActorRef; // 0x00
		TESForm* infection;					  // 0x04
	};

	static_assert(sizeof(BGSInfectionEvent) == 0x10);
}

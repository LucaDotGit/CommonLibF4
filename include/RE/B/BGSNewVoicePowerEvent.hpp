#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSNewVoicePowerEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSNewVoicePowerEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 00
		TESForm* voicePower;	  // 04
	};
	static_assert(sizeof(BGSNewVoicePowerEvent) == 0x10);
}

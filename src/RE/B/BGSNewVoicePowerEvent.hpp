#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSNewVoicePowerEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSNewVoicePowerEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 0x00
		TESForm* voicePower;	  // 0x04
	};

	static_assert(sizeof(BGSNewVoicePowerEvent) == 0x10);
}

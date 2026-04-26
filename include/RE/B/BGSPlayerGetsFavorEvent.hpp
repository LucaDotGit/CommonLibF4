#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPlayerGetsFavorEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSPlayerGetsFavorEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 00
	};
	static_assert(sizeof(BGSPlayerGetsFavorEvent) == 0x04);
}

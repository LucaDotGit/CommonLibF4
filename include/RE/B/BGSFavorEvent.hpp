#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSFavorEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSFavorEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;				// 00
		ObjectRefHandle requestingActorRef; // 08
	};
	static_assert(sizeof(BGSFavorEvent) == 0x10);
}

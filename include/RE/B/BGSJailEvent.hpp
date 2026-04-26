#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSJailEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSJailEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle guardRef; // 00
		TESForm* crimeGroup;	  // 08
		BGSLocation* location;	  // 10
		std::uint32_t crimeGold;  // 18
	};
	static_assert(sizeof(BGSJailEvent) == 0x20);
}

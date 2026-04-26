#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSArrestEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSArrestEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle guardRef;	 // 00
		ObjectRefHandle criminalRef; // 04
		BGSLocation* location;		 // 08
		std::int32_t crimeType;		 // 10
	};
	static_assert(sizeof(BGSArrestEvent) == 0x18);
}

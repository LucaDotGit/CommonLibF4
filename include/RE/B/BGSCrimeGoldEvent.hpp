#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCrimeGoldEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSCrimeGoldEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;	 // 00
		ObjectRefHandle criminalRef; // 04
		TESForm* faction;			 // 08
		std::uint32_t goldAmount;	 // 10
		std::int32_t crimeType;		 // 14
	};
	static_assert(sizeof(BGSCrimeGoldEvent) == 0x18);
}

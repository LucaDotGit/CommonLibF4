#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCrimeGoldEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSCrimeGoldEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;	 // 0x00
		ObjectRefHandle criminalRef; // 0x04
		TESForm* faction;			 // 0x08
		std::uint32_t goldAmount;	 // 0x10
		std::int32_t crimeType;		 // 0x14
	};

	static_assert(sizeof(BGSCrimeGoldEvent) == 0x18);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPayFine
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSPayFine::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle criminalRef; // 00
		ObjectRefHandle guardRef;	 // 04
		TESForm* crimeGroup;		 // 08
		std::uint32_t crimeGoldPaid; // 10
	};
	static_assert(sizeof(BGSPayFine) == 0x18);
}

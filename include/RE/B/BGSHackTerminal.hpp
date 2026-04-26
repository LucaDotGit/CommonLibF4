#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSHackTerminal
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSHackTerminal::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle terminalRef; // 00
		std::uint32_t success;		 // 04
	};
	static_assert(sizeof(BGSHackTerminal) == 0x08);
}

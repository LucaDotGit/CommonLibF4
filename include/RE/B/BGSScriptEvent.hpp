#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSScriptEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSScriptEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSKeyword* keyword;   // 00
		BGSLocation* location; // 08
		ObjectRefHandle ref01; // 10
		ObjectRefHandle ref02; // 14
		std::uint32_t value01; // 18
		std::uint32_t value02; // 1C
	};
	static_assert(sizeof(BGSScriptEvent) == 0x20);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSJailEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSJailEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle guardRef; // 0x00
		TESForm* crimeGroup;	  // 0x08
		BGSLocation* location;	  // 0x10
		std::uint32_t crimeGold;  // 0x18
	};

	static_assert(sizeof(BGSJailEvent) == 0x20);
}

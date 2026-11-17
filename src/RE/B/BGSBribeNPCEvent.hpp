#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSBribeNPCEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSBribeNPCEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 0x00
		std::uint32_t goldAmount; // 0x04
	};

	static_assert(sizeof(BGSBribeNPCEvent) == 0x08);
}

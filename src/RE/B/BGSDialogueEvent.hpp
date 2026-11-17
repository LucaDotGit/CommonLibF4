#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSDialogueEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSDialogueEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;		// 0x00
		ObjectRefHandle actorRef01; // 0x08
		ObjectRefHandle actorRef02; // 0x0C
	};

	static_assert(sizeof(BGSDialogueEvent) == 0x10);
}

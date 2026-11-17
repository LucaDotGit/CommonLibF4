#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSChangeLocationEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSChangeLocationEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 0x00
		BGSLocation* oldLocation; // 0x08
		BGSLocation* newLocation; // 0x10
	};

	static_assert(sizeof(BGSChangeLocationEvent) == 0x18);
}

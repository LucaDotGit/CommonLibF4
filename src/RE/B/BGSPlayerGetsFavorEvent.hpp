#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPlayerGetsFavorEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSPlayerGetsFavorEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 0x00
	};

	static_assert(sizeof(BGSPlayerGetsFavorEvent) == 0x04);
}

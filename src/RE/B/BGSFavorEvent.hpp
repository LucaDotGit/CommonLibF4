#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSFavorEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSFavorEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;				// 0x00
		ObjectRefHandle requestingActorRef; // 0x08
	};

	static_assert(sizeof(BGSFavorEvent) == 0x10);
}

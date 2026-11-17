#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSCastMagicEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSCastMagicEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle castingActorRef; // 0x00
		ObjectRefHandle spellTargetRef;	 // 0x04
		BGSLocation* location;			 // 0x08
		std::uint32_t crimeType;		 // 0x10
	};

	static_assert(sizeof(BGSCastMagicEvent) == 0x18);
}

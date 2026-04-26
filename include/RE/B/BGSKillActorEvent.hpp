#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t;

	class BGSKillActorEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSKillActorEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;														 // 00
		ObjectRefHandle killerRef;														 // 04
		BGSLocation* location;															 // 08
		std::uint32_t crimeStatus;														 // 10
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> relationshipRankToKillerBeforeDeath; // 14
	};
	static_assert(sizeof(BGSKillActorEvent) == 0x18);
}

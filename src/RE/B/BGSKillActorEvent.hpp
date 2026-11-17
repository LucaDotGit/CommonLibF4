#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t;

	class BGSKillActorEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSKillActorEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;														 // 0x00
		ObjectRefHandle killerRef;														 // 0x04
		BGSLocation* location;															 // 0x08
		std::uint32_t crimeStatus;														 // 0x10
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> relationshipRankToKillerBeforeDeath; // 0x14
	};

	static_assert(sizeof(BGSKillActorEvent) == 0x18);
}

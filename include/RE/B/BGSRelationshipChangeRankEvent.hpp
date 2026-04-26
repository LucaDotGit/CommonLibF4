#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t;

	class BGSRelationshipChangeRankEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSRelationshipChangeRankEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef01;							 // 00
		ObjectRefHandle actorRef02;							 // 04
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> oldRank; // 00
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> newRank; // 04
	};
	static_assert(sizeof(BGSRelationshipChangeRankEvent) == 0x10);
}

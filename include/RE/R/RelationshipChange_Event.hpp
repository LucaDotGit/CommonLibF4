#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t;
}

namespace RE::RelationshipChange
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::RelationshipChange::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESNPC* withThisNPC;										 // 00
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> oldRelationship; // 08
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> newRelationship; // 0C
	};
	static_assert(sizeof(Event) == 0x10);
}

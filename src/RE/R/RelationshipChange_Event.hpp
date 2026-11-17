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
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::RelationshipChange::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESNPC* withThisNPC;										 // 0x00
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> oldRelationship; // 0x08
		REX::Enum<RELATIONSHIP_LEVEL, std::int32_t> newRelationship; // 0x0C
	};

	static_assert(sizeof(Event) == 0x10);
}

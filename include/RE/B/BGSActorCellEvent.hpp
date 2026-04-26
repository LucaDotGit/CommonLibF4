#pragma once

#include "RE/B/BGSActorEvent.hpp"

namespace RE
{
	class BGSActorCellEvent
		: public BGSActorEvent // 00
	{
	public:
		enum class EventType : std::int32_t
		{
			kEnter = 0,
			kLeave = 1
		};

		// members
		TESFormID cellFormID;						  // 04
		REX::Enum<EventType, std::int32_t> eventType; // 08
	};
	static_assert(sizeof(BGSActorCellEvent) == 0x0C);
}

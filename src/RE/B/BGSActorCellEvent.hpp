#pragma once

#include "RE/B/BGSActorEvent.hpp"

namespace RE
{
	class BGSActorCellEvent : public BGSActorEvent // 0x00
	{
	public:
		enum class EventType : std::int32_t
		{
			Enter = 0,
			Leave = 1
		};

		// members
		TESFormID cellFormID;						  // 0x04
		REX::Enum<EventType, std::int32_t> eventType; // 0x08
	};

	static_assert(sizeof(BGSActorCellEvent) == 0x0C);
}

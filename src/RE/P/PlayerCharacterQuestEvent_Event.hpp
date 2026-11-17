#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSInstancedQuestObjective;
}

namespace RE::PlayerCharacterQuestEvent
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			AddObjective = 0,
			UpdateObjective = 1,
			RemoveQuest = 2,
			RemoveQuestTarget = 3,
			UpdateQuestTarget = 4
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerCharacterQuestEvent::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 0x00
		BGSInstancedQuestObjective* pQuestObjective;  // 0x04
	};

	static_assert(sizeof(Event) == 0x10);
}

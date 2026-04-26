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
			kAddObjective = 0,
			kUpdateObjective = 1,
			kRemoveQuest = 2,
			kRemoveQuestTarget = 3,
			kUpdateQuestTarget = 4
		};

		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerCharacterQuestEvent::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 00
		BGSInstancedQuestObjective* pQuestObjective;  // 04
	};
	static_assert(sizeof(Event) == 0x10);
}

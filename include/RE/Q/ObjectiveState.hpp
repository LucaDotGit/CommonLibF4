#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class QUEST_OBJECTIVE_STATE : std::int32_t;

	class BGSQuestObjective;
}

namespace RE::ObjectiveState
{
	class Event
	{
	public:
		// members
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int32_t> oldState; // 00
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int32_t> newState; // 04
		BGSQuestObjective* objective;							 // 08
	};
	static_assert(sizeof(Event) == 0x10);

	[[nodiscard]] inline BSTEventSource<Event>* GetEventSource()
	{
		using FuncType = decltype(&ObjectiveState::GetEventSource);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ObjectiveState::GetEventSource };
		return std::invoke(FUNC);
	}
}

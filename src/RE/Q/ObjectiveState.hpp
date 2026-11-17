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
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int32_t> oldState; // 0x00
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int32_t> newState; // 0x04
		BGSQuestObjective* objective;							 // 0x08
	};

	static_assert(sizeof(Event) == 0x10);

	[[nodiscard]]
	inline auto GetEventSource() -> BSTEventSource<Event>*
	{
		using FuncType = decltype(&ObjectiveState::GetEventSource);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ObjectiveState::GetEventSource);
		return std::invoke(FUNC);
	}
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESQuestStartStopEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESQuestStartStopEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESQuestStartStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuestStartStopEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID questFormID; // 00
		bool started;		   // 04
		bool failed;		   // 05
	};
	static_assert(sizeof(TESQuestStartStopEvent) == 0x08);
}

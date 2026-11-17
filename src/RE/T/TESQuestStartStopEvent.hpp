#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESQuestStartStopEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESQuestStartStopEvent>*
		{
			using FuncType = decltype(&TESQuestStartStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESQuestStartStopEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID questFormID; // 0x00
		bool started;		   // 0x04
		bool failed;		   // 0x05
	};

	static_assert(sizeof(TESQuestStartStopEvent) == 0x08);
}

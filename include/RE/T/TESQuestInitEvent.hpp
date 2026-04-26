#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESQuestInitEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESQuestInitEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESQuestInitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuestInitEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID questFormID; // 00
	};
	static_assert(sizeof(TESQuestInitEvent) == 0x04);
}

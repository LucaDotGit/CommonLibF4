#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESQuestStageItemDoneEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESQuestStageItemDoneEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESQuestStageItemDoneEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuestStageItemDoneEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID questFormID; // 00
		std::uint16_t stageID; // 04
		std::uint8_t itemID;   // 08
	};
	static_assert(sizeof(TESQuestStageItemDoneEvent) == 0x08);
}

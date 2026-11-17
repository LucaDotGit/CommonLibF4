#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESQuestStageItemDoneEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESQuestStageItemDoneEvent>*
		{
			using FuncType = decltype(&TESQuestStageItemDoneEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESQuestStageItemDoneEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID questFormID; // 0x00
		std::uint16_t stageID; // 0x04
		std::uint8_t itemID;   // 0x08
	};

	static_assert(sizeof(TESQuestStageItemDoneEvent) == 0x08);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class TESQuestStageEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESQuestStageEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESQuestStageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESQuestStageEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 00
		TESFormID questFormID;										  // 08
		std::uint16_t stageID;										  // 0C
		std::uint8_t itemID;										  // 0E
	};
	static_assert(sizeof(TESQuestStageEvent) == 0x10);
}

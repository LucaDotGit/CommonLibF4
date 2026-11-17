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
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESQuestStageEvent>*
		{
			using FuncType = decltype(&TESQuestStageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESQuestStageEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 0x00
		TESFormID questFormID;										  // 0x08
		std::uint16_t stageID;										  // 0x0C
		std::uint8_t itemID;										  // 0x0E
	};

	static_assert(sizeof(TESQuestStageEvent) == 0x10);
}

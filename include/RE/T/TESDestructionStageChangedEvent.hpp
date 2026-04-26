#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDestructionStageChangedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESDestructionStageChangedEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESDestructionStageChangedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDestructionStageChangedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
		std::uint32_t oldStage;		  // 08
		std::uint32_t newStage;		  // 0C
	};
	static_assert(sizeof(TESDestructionStageChangedEvent) == 0x10);
}

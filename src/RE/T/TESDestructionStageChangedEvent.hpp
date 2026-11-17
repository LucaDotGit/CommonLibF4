#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDestructionStageChangedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESDestructionStageChangedEvent>*
		{
			using FuncType = decltype(&TESDestructionStageChangedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESDestructionStageChangedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 0x00
		std::uint32_t oldStage;		  // 0x08
		std::uint32_t newStage;		  // 0x0C
	};

	static_assert(sizeof(TESDestructionStageChangedEvent) == 0x10);
}

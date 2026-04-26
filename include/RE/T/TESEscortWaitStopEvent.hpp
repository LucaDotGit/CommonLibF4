#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEscortWaitStopEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESEscortWaitStopEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESEscortWaitStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESEscortWaitStopEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> escortRef; // 00
	};
	static_assert(sizeof(TESEscortWaitStopEvent) == 0x08);
}

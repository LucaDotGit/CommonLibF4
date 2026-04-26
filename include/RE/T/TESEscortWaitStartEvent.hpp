#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEscortWaitStartEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESEscortWaitStartEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESEscortWaitStartEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESEscortWaitStartEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> escortRef; // 00
	};
	static_assert(sizeof(TESEscortWaitStartEvent) == 0x08);
}

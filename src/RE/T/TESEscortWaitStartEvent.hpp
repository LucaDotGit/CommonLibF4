#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEscortWaitStartEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESEscortWaitStartEvent>*
		{
			using FuncType = decltype(&TESEscortWaitStartEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESEscortWaitStartEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> escortRef; // 0x00
	};

	static_assert(sizeof(TESEscortWaitStartEvent) == 0x08);
}

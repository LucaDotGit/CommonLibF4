#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEnterSneakingEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESEnterSneakingEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESEnterSneakingEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESEnterSneakingEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
	};
	static_assert(sizeof(TESEnterSneakingEvent) == 0x08);
}

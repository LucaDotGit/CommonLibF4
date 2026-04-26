#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSwitchRaceCompleteEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESSwitchRaceCompleteEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSwitchRaceCompleteEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSwitchRaceCompleteEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
	};
	static_assert(sizeof(TESSwitchRaceCompleteEvent) == 0x08);
}

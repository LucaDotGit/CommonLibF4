#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSwitchRaceCompleteEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSwitchRaceCompleteEvent>*
		{
			using FuncType = decltype(&TESSwitchRaceCompleteEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSwitchRaceCompleteEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 0x00
	};

	static_assert(sizeof(TESSwitchRaceCompleteEvent) == 0x08);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSleepStopEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESSleepStopEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSleepStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSleepStopEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		bool interrupted;				 // 00
		NiPointer<TESObjectREFR> bedRef; // 08
	};
	static_assert(sizeof(TESSleepStopEvent) == 0x10);
}

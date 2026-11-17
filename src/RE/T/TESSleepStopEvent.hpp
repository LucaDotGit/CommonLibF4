#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSleepStopEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSleepStopEvent>*
		{
			using FuncType = decltype(&TESSleepStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSleepStopEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		bool interrupted;				 // 0x00
		NiPointer<TESObjectREFR> bedRef; // 0x08
	};

	static_assert(sizeof(TESSleepStopEvent) == 0x10);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSleepStartEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSleepStartEvent>*
		{
			using FuncType = decltype(&TESSleepStartEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSleepStartEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Float32 startTime;			 // 0x00
		REX::Float32 desiredEndTime;	 // 0x04
		NiPointer<TESObjectREFR> bedRef; // 0x08
	};

	static_assert(sizeof(TESSleepStartEvent) == 0x10);
}

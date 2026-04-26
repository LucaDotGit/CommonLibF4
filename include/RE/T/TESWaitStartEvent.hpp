#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESWaitStartEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESWaitStartEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESWaitStartEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWaitStartEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Float32 startTime;		 // 00
		REX::Float32 desiredEndTime; // 04
	};
	static_assert(sizeof(TESWaitStartEvent) == 0x08);
}

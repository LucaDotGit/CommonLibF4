#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESWaitStopEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESWaitStopEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESWaitStopEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWaitStopEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		bool interrupted; // 00
	};
	static_assert(sizeof(TESWaitStopEvent) == 0x01);
}

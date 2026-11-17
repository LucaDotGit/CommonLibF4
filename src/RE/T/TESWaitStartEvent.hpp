#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESWaitStartEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESWaitStartEvent>*
		{
			using FuncType = decltype(&TESWaitStartEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESWaitStartEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Float32 startTime;		 // 0x00
		REX::Float32 desiredEndTime; // 0x04
	};

	static_assert(sizeof(TESWaitStartEvent) == 0x08);
}

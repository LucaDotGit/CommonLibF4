#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESTrackedStatsEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESTrackedStatsEvent>*
		{
			using FuncType = decltype(&TESTrackedStatsEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTrackedStatsEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		BSFixedString statID;  // 0x00
		std::int32_t newValue; // 0x08
	};

	static_assert(sizeof(TESTrackedStatsEvent) == 0x10);
}

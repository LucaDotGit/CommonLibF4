#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Bounty
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Bounty::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFaction* faction;	// 0x00
		std::int32_t newBounty; // 0x04
		std::int32_t oldBounty; // 0x08
	};

	static_assert(sizeof(Event) == 0x10);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Bounty
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Bounty::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFaction* faction;	// 00
		std::int32_t newBounty; // 04
		std::int32_t oldBounty; // 08
	};
	static_assert(sizeof(Event) == 0x10);
}

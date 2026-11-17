#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::FatmanDeaths
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::FatmanDeaths::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		Actor* victimActor; // 0x00
	};

	static_assert(sizeof(Event) == 0x08);
}

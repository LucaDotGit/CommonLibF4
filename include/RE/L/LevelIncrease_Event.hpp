#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::LevelIncrease
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::LevelIncrease::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		std::uint32_t newLevel; // 00
	};
	static_assert(sizeof(Event) == 0x04);
}

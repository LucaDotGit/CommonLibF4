#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::ItemSteal
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&ItemSteal::Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ItemSteal::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		std::uint32_t numStolen; // 00
	};
	static_assert(sizeof(Event) == 0x04);
}

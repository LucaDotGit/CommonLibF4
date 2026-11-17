#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::ItemSteal
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&ItemSteal::Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ItemSteal::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		std::uint32_t numStolen; // 0x00
	};

	static_assert(sizeof(Event) == 0x04);
}

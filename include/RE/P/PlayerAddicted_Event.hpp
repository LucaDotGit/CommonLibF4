#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::PlayerAddicted
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerAddicted::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		AlchemyItem* chem; // 00
	};
	static_assert(sizeof(Event) == 0x08);
}

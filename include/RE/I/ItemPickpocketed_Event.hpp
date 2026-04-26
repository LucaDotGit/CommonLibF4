#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::ItemPickpocketed
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemPickpocketed::Event>* GetEventSource()
		{
			using FuncType = decltype(&ItemPickpocketed::Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ItemPickpocketed::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		Actor* pickerActor;	 // 00
		Actor* victimActor;	 // 08
		bool firstItemTaken; // 10
	};
	static_assert(sizeof(Event) == 0x18);
}

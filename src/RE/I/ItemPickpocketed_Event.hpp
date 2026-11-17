#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::ItemPickpocketed
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemPickpocketed::Event>*
		{
			using FuncType = decltype(&ItemPickpocketed::Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ItemPickpocketed::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		Actor* pickerActor;	 // 0x00
		Actor* victimActor;	 // 0x08
		bool firstItemTaken; // 0x10
	};

	static_assert(sizeof(Event) == 0x18);
}

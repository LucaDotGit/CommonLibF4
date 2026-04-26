#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::ItemCrafted
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ItemCrafted::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFurniture* workbench;
		BGSConstructibleObject* recipe;
	};
	static_assert(sizeof(Event) == 0x10);
}

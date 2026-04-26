#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemGrabbedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemGrabbedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemGrabbedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemGrabbedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		NiPointer<TESObjectREFR> itemRef;	  // 08
	};
	static_assert(sizeof(ItemGrabbedEvent) == 0x10);
}

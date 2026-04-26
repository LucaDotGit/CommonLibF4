#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemPlacedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemPlacedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemPlacedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemPlacedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		NiPointer<TESObjectREFR> itemRef;	  // 08
	};
	static_assert(sizeof(ItemPlacedEvent) == 0x10);
}

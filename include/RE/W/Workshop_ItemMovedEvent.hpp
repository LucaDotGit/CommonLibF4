#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemMovedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemMovedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemMovedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemMovedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		NiPointer<TESObjectREFR> itemRef;	  // 08
	};
	static_assert(sizeof(ItemMovedEvent) == 0x10);
}

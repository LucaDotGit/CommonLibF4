#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemRepairedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemRepairedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemRepairedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemRepairedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		NiPointer<TESObjectREFR> itemRef;	  // 08
	};
	static_assert(sizeof(ItemRepairedEvent) == 0x10);
}

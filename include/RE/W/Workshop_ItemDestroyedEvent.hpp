#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemDestroyedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemDestroyedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemDestroyedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemDestroyedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		NiPointer<TESObjectREFR> itemRef;	  // 08
	};
	static_assert(sizeof(ItemDestroyedEvent) == 0x10);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemRepairedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemRepairedEvent>*
		{
			using FuncType = decltype(&ItemRepairedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ItemRepairedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		NiPointer<TESObjectREFR> itemRef;	  // 0x08
	};

	static_assert(sizeof(ItemRepairedEvent) == 0x10);
}

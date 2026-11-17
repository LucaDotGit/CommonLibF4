#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemPlacedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemPlacedEvent>*
		{
			using FuncType = decltype(&ItemPlacedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ItemPlacedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		NiPointer<TESObjectREFR> itemRef;	  // 0x08
	};

	static_assert(sizeof(ItemPlacedEvent) == 0x10);
}

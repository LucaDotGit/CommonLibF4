#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemMovedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemMovedEvent>*
		{
			using FuncType = decltype(&ItemMovedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ItemMovedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		NiPointer<TESObjectREFR> itemRef;	  // 0x08
	};

	static_assert(sizeof(ItemMovedEvent) == 0x10);
}

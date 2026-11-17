#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemGrabbedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemGrabbedEvent>*
		{
			using FuncType = decltype(&ItemGrabbedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ItemGrabbedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		NiPointer<TESObjectREFR> itemRef;	  // 0x08
	};

	static_assert(sizeof(ItemGrabbedEvent) == 0x10);
}

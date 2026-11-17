#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class ItemDestroyedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemDestroyedEvent>*
		{
			using FuncType = decltype(&ItemDestroyedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ItemDestroyedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		NiPointer<TESObjectREFR> itemRef;	  // 0x08
	};

	static_assert(sizeof(ItemDestroyedEvent) == 0x10);
}

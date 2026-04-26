#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Workshop
{
	class ItemScrappedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemScrappedEvent>* GetEventSource()
		{
			using FuncType = decltype(&ItemScrappedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ItemScrappedEvent::GetEventSource };
			return std::invoke(FUNC);
		}
	};
	static_assert(std::is_empty_v<ItemScrappedEvent>);
}

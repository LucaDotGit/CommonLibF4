#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::TESHarvestEvent
{
	class ItemHarvested
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<ItemHarvested>*
		{
			using FuncType = decltype(&ItemHarvested::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESHarvestEvent::ItemHarvested::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESBoundObject* harvestedItem; // 0x00
		TESObjectREFR* harvestedRef;   // 0x08
		Actor* harvesterActor;		   // 0x10
	};

	static_assert(sizeof(ItemHarvested) == 0x18);
}

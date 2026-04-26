#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::TESHarvestEvent
{
	class ItemHarvested
	{
	public:
		[[nodiscard]] static BSTEventSource<ItemHarvested>* GetEventSource()
		{
			using FuncType = decltype(&ItemHarvested::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESHarvestEvent::ItemHarvested::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESBoundObject* harvestedItem; // 00
		TESObjectREFR* harvestedRef;   // 08
		Actor* harvesterActor;		   // 10
	};
	static_assert(sizeof(ItemHarvested) == 0x18);
}

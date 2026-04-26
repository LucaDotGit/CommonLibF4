#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESExitFurnitureEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESExitFurnitureEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESExitFurnitureEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESExitFurnitureEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> furnitureRef; // 00
		NiPointer<TESObjectREFR> actionRef;	   // 08
	};
	static_assert(sizeof(TESExitFurnitureEvent) == 0x10);
}

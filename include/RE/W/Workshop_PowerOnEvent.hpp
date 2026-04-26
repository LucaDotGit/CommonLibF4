#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class PowerOnEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<PowerOnEvent>* GetEventSource()
		{
			using FuncType = decltype(&PowerOnEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::PowerOnEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> itemRef;		 // 00
		NiPointer<TESObjectREFR> powerSourceRef; // 08
	};
	static_assert(sizeof(PowerOnEvent) == 0x10);
}

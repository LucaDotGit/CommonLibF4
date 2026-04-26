#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class PowerOffEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<PowerOffEvent>* GetEventSource()
		{
			using FuncType = decltype(&PowerOffEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::PowerOffEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> itemRef; // 00
	};
	static_assert(sizeof(PowerOffEvent) == 0x08);
}

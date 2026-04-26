#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEnterBleedoutEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESEnterBleedoutEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESEnterBleedoutEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESEnterBleedoutEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
	};
	static_assert(sizeof(TESEnterBleedoutEvent) == 0x08);
}

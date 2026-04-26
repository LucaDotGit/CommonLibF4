#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESActivateEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESActivateEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESActivateEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESActivateEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> activatedRef; // 00
		NiPointer<TESObjectREFR> actionRef;	   // 08
	};
	static_assert(sizeof(TESActivateEvent) == 0x10);
}

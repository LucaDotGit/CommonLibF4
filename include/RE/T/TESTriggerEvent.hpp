#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESTriggerEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESTriggerEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESTriggerEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTriggerEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> triggerRef; // 00
		NiPointer<TESObjectREFR> actionRef;	 // 08
	};
	static_assert(sizeof(TESTriggerEvent) == 0x10);
}

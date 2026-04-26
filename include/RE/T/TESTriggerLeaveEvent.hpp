#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESTriggerLeaveEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESTriggerLeaveEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESTriggerLeaveEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTriggerLeaveEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> triggerRef; // 00
		NiPointer<TESObjectREFR> actionRef;	 // 08
	};
	static_assert(sizeof(TESTriggerLeaveEvent) == 0x10);
}

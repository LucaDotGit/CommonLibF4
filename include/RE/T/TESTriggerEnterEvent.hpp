#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESTriggerEnterEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESTriggerEnterEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESTriggerEnterEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTriggerEnterEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> triggerRef; // 00
		NiPointer<TESObjectREFR> actionRef;	 // 08
	};
	static_assert(sizeof(TESTriggerEnterEvent) == 0x10);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESTriggerLeaveEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESTriggerLeaveEvent>*
		{
			using FuncType = decltype(&TESTriggerLeaveEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTriggerLeaveEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> triggerRef; // 0x00
		NiPointer<TESObjectREFR> actionRef;	 // 0x08
	};

	static_assert(sizeof(TESTriggerLeaveEvent) == 0x10);
}

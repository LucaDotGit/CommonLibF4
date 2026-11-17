#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESTriggerEnterEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESTriggerEnterEvent>*
		{
			using FuncType = decltype(&TESTriggerEnterEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTriggerEnterEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> triggerRef; // 0x00
		NiPointer<TESObjectREFR> actionRef;	 // 0x08
	};

	static_assert(sizeof(TESTriggerEnterEvent) == 0x10);
}

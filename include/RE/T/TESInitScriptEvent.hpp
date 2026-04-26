#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESInitScriptEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESInitScriptEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESInitScriptEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESInitScriptEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> initializedRef; // 00
	};
	static_assert(sizeof(TESInitScriptEvent) == 0x08);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESConsciousnessEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESConsciousnessEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESConsciousnessEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESConsciousnessEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 00
		bool unconscious;					// 08
	};
	static_assert(sizeof(TESConsciousnessEvent) == 0x10);
}

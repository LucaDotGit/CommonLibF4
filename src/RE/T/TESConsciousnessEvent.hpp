#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESConsciousnessEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESConsciousnessEvent>*
		{
			using FuncType = decltype(&TESConsciousnessEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESConsciousnessEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 0x00
		bool unconscious;					// 0x08
	};

	static_assert(sizeof(TESConsciousnessEvent) == 0x10);
}

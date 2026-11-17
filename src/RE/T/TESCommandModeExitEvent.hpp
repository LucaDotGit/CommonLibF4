#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESCommandModeExitEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESCommandModeExitEvent>*
		{
			using FuncType = decltype(&TESCommandModeExitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCommandModeExitEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 0x00
	};

	static_assert(sizeof(TESCommandModeExitEvent) == 0x08);
}

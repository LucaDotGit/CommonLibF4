#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESCommandModeEnterEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCommandModeEnterEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCommandModeEnterEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCommandModeEnterEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 00
	};
	static_assert(sizeof(TESCommandModeEnterEvent) == 0x08);
}

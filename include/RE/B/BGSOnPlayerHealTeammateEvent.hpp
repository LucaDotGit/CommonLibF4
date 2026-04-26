#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerHealTeammateEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerHealTeammateEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerHealTeammateEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerHealTeammateEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> teammateRef; // 00
	};
	static_assert(sizeof(BGSOnPlayerHealTeammateEvent) == 0x08);
}

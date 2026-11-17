#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerHealTeammateEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSOnPlayerHealTeammateEvent>*
		{
			using FuncType = decltype(&BGSOnPlayerHealTeammateEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOnPlayerHealTeammateEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> teammateRef; // 0x00
	};

	static_assert(sizeof(BGSOnPlayerHealTeammateEvent) == 0x08);
}

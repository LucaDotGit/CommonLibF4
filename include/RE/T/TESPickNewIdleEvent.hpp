#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPickNewIdleEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESPickNewIdleEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESPickNewIdleEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESPickNewIdleEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 00
	};
	static_assert(sizeof(TESPickNewIdleEvent) == 0x08);
}

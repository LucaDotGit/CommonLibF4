#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPickNewIdleEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESPickNewIdleEvent>*
		{
			using FuncType = decltype(&TESPickNewIdleEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESPickNewIdleEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 0x00
	};

	static_assert(sizeof(TESPickNewIdleEvent) == 0x08);
}

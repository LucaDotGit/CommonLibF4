#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPickpocketFailedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESPickpocketFailedEvent>*
		{
			using FuncType = decltype(&TESPickpocketFailedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESPickpocketFailedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		NiPointer<TESObjectREFR> victimRef; // 0x00
	};

	static_assert(sizeof(TESPickpocketFailedEvent) == 0x08);
}

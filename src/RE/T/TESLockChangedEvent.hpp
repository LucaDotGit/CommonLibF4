#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESLockChangedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESLockChangedEvent>*
		{
			using FuncType = decltype(&TESLockChangedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESLockChangedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> lockedRef; // 0x00
	};

	static_assert(sizeof(TESLockChangedEvent) == 0x08);
}

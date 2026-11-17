#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDeathEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESDeathEvent>*
		{
			using FuncType = decltype(&TESDeathEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESDeathEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> dyingActorRef;	 // 0x00
		NiPointer<TESObjectREFR> killerActorRef; // 0x08
		bool dying;								 // 0x10
	};

	static_assert(sizeof(TESDeathEvent) == 0x18);
}

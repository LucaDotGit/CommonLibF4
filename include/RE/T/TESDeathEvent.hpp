#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDeathEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESDeathEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESDeathEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDeathEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> dyingActorRef;	 // 00
		NiPointer<TESObjectREFR> killerActorRef; // 08
		bool dying;								 // 10
	};
	static_assert(sizeof(TESDeathEvent) == 0x18);
}

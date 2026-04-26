#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::CriticalHitEvent
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::CriticalHitEvent::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		Actor* attackerActor;  // 00
		TESObjectWEAP* weapon; // 08
		bool sneakAttack;	   // 10
	};
	static_assert(sizeof(Event) == 0x18);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::CriticalHitEvent
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::CriticalHitEvent::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		Actor* attackerActor;  // 0x00
		TESObjectWEAP* weapon; // 0x08
		bool sneakAttack;	   // 0x10
	};

	static_assert(sizeof(Event) == 0x18);
}

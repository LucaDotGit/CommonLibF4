#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESActorLocationChangeEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESActorLocationChangeEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESActorLocationChangeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESActorLocationChangeEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 00
		BGSLocation* oldLocation;		   // 08
		BGSLocation* newLocation;		   // 10
	};
	static_assert(sizeof(TESActorLocationChangeEvent) == 0x18);
}

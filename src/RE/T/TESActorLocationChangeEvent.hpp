#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESActorLocationChangeEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESActorLocationChangeEvent>*
		{
			using FuncType = decltype(&TESActorLocationChangeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESActorLocationChangeEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 0x00
		BGSLocation* oldLocation;		   // 0x08
		BGSLocation* newLocation;		   // 0x10
	};

	static_assert(sizeof(TESActorLocationChangeEvent) == 0x18);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDeferredKillEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESDeferredKillEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESDeferredKillEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESDeferredKillEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> dyingActorRef;	 // 00
		NiPointer<TESObjectREFR> killerActorRef; // 08
	};
	static_assert(sizeof(TESDeferredKillEvent) == 0x10);
}

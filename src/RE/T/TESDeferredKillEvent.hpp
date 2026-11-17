#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESDeferredKillEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESDeferredKillEvent>*
		{
			using FuncType = decltype(&TESDeferredKillEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESDeferredKillEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> dyingActorRef;	 // 0x00
		NiPointer<TESObjectREFR> killerActorRef; // 0x08
	};

	static_assert(sizeof(TESDeferredKillEvent) == 0x10);
}

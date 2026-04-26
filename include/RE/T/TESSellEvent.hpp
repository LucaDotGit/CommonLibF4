#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSellEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESSellEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSellEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSellEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sellerActorRef; // 00
		TESFormID buyerFormID;					 // 08
		ContainerID uniqueID;					 // 0C
	};
	static_assert(sizeof(TESSellEvent) == 0x10);
}

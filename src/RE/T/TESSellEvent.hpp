#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSellEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSellEvent>*
		{
			using FuncType = decltype(&TESSellEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSellEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sellerActorRef; // 0x00
		TESFormID buyerFormID;					 // 0x08
		ContainerID uniqueID;					 // 0x0C
	};

	static_assert(sizeof(TESSellEvent) == 0x10);
}

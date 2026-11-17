#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPackageEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			Begin = 0,
			End = 1,
			Change = 2
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESPackageEvent>*
		{
			using FuncType = decltype(&TESPackageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESPackageEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef;			  // 0x00
		TESFormID packageFormID;					  // 0x08
		REX::Enum<EventType, std::int32_t> eventType; // 0x0C
	};

	static_assert(sizeof(TESPackageEvent) == 0x10);
}

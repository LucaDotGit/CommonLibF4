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
			kBegin = 0,
			kEnd = 1,
			kChange = 2
		};

		[[nodiscard]] static BSTEventSource<TESPackageEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESPackageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESPackageEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef;			  // 00
		TESFormID packageFormID;					  // 08
		REX::Enum<EventType, std::int32_t> eventType; // 0C
	};
	static_assert(sizeof(TESPackageEvent) == 0x10);
}

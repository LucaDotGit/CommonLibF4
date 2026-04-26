#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESFurnitureEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kEnter = 0,
			kExit = 1
		};

		[[nodiscard]] static BSTEventSource<TESFurnitureEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESFurnitureEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFurnitureEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef;			  // 00
		NiPointer<TESObjectREFR> furnitureRef;		  // 08
		REX::Enum<EventType, std::int32_t> eventType; // 10
	};
	static_assert(sizeof(TESFurnitureEvent) == 0x18);
}

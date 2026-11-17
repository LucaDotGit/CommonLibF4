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
			Enter = 0,
			Exit = 1
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESFurnitureEvent>*
		{
			using FuncType = decltype(&TESFurnitureEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESFurnitureEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef;			  // 0x00
		NiPointer<TESObjectREFR> furnitureRef;		  // 0x08
		REX::Enum<EventType, std::int32_t> eventType; // 0x10
	};

	static_assert(sizeof(TESFurnitureEvent) == 0x18);
}

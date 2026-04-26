#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::PlayerActiveEffectChanged
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			kAdded = 0,
			kRemoved = 1,
			kStatusChanged = 2
		};

		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerActiveEffectChanged::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<ActiveEffect> effect;		  // 00
		REX::Enum<EventType, std::int32_t> eventType; // 08
	};
	static_assert(sizeof(Event) == 0x10);
}

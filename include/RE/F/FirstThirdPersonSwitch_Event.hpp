#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::FirstThirdPersonSwitch
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			kFirstPerson = 0,
			kThirdPerson = 1
		};

		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::FirstThirdPersonSwitch::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> oldEventType; // 00
		REX::Enum<EventType, std::int32_t> newEventType; // 04
	};
	static_assert(sizeof(Event) == 0x08);
};

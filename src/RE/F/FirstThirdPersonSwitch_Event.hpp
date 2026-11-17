#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::FirstThirdPersonSwitch
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			FirstPerson = 0,
			ThirdPerson = 1
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::FirstThirdPersonSwitch::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<EventType, std::int32_t> oldEventType; // 0x00
		REX::Enum<EventType, std::int32_t> newEventType; // 0x04
	};

	static_assert(sizeof(Event) == 0x08);
};

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
			Added = 0,
			Removed = 1,
			StatusChanged = 2
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerActiveEffectChanged::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<ActiveEffect> effect;		  // 0x00
		REX::Enum<EventType, std::int32_t> eventType; // 0x08
	};

	static_assert(sizeof(Event) == 0x10);
}

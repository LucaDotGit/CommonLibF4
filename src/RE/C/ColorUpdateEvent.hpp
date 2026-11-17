#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ColorUpdateEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<ColorUpdateEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE = REL::Relocation<EventSourceType**>(ID::ColorUpdateEvent::GetEventSource);
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(std::is_empty_v<ColorUpdateEvent>);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ColorUpdateEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<ColorUpdateEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::ColorUpdateEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(std::addressof(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller));
			}

			return *SINGLETON;
		}
	};
	static_assert(std::is_empty_v<ColorUpdateEvent>);
}

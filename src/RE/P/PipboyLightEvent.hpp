#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PipboyLightEvent : public BSTValueEvent<bool> // 0x00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PipboyLightEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE = REL::Relocation<EventSourceType**>(ID::PipboyLightEvent::GetEventSource);
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(sizeof(PipboyLightEvent) == 0x02);
}

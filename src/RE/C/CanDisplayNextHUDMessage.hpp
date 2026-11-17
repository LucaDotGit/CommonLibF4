#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CanDisplayNextHUDMessage : public BSTValueEvent<bool> // 0x00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<CanDisplayNextHUDMessage>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::CanDisplayNextHUDMessage::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(sizeof(CanDisplayNextHUDMessage) == 0x02);
}

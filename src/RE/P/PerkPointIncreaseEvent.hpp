#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PerkPointIncreaseEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PerkPointIncreaseEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::PerkPointIncreaseEvent::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}

		// members
		std::uint8_t newCount; // 0x00
	};

	static_assert(sizeof(PerkPointIncreaseEvent) == 0x01);
}

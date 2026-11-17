#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class DoBeforeNewOrLoadCompletedEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<DoBeforeNewOrLoadCompletedEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::DoBeforeNewOrLoadCompletedEvent::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(std::is_empty_v<DoBeforeNewOrLoadCompletedEvent>);
}

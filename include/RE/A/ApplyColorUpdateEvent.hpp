#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ApplyColorUpdateEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<ApplyColorUpdateEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::ApplyColorUpdateEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(std::is_empty_v<ApplyColorUpdateEvent>);
}

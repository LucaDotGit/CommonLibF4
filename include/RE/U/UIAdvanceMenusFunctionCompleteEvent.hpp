#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class UIAdvanceMenusFunctionCompleteEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<UIAdvanceMenusFunctionCompleteEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::UIAdvanceMenusFunctionCompleteEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(std::is_empty_v<UIAdvanceMenusFunctionCompleteEvent>);
}

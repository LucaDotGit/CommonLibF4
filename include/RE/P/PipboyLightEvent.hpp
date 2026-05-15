#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PipboyLightEvent
		: public BSTValueEvent<bool> // 00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PipboyLightEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::PipboyLightEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(sizeof(PipboyLightEvent) == 0x02);
}

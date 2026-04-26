#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CanDisplayNextHUDMessage
		: public BSTValueEvent<bool> // 00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<CanDisplayNextHUDMessage>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::CanDisplayNextHUDMessage::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(std::addressof(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller));
			}

			return *SINGLETON;
		}
	};
	static_assert(sizeof(CanDisplayNextHUDMessage) == 0x02);
}

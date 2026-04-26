#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PerkPointIncreaseEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PerkPointIncreaseEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::PerkPointIncreaseEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(std::addressof(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller));
			}

			return *SINGLETON;
		}

		// members
		std::uint8_t newCount; // 00
	};
	static_assert(sizeof(PerkPointIncreaseEvent) == 0x01);
}

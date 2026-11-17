#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class HUDModeType;

	class HUDModeEvent
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<HUDModeEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE = REL::Relocation<EventSourceType**>(ID::HUDModeEvent::GetEventSource);
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}

		// members
		BSTArray<HUDModeType>* currentHUDModes; // 0x00
	};

	static_assert(sizeof(HUDModeEvent) == 0x08);
}

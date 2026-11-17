#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PowerArmorLightData
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PowerArmorLightData>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::PowerArmorLightData::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}

		// members
		bool lightOn; // 0x00
	};

	static_assert(sizeof(PowerArmorLightData) == 0x01);
}

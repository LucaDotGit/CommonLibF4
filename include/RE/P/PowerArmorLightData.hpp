#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PowerArmorLightData
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PowerArmorLightData>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::PowerArmorLightData::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(std::addressof(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller));
			}

			return *SINGLETON;
		}

		// members
		bool lightOn; // 00
	};
	static_assert(sizeof(PowerArmorLightData) == 0x01);
}

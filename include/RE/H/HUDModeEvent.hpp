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
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::HUDModeEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(std::addressof(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller));
			}

			return *SINGLETON;
		}

		// members
		BSTArray<HUDModeType>* currentHUDModes; // 00
	};
	static_assert(sizeof(HUDModeEvent) == 0x08);
}

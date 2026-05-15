#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/V/ViewCasterUpdateData.hpp"

namespace RE
{
	class ViewCasterUpdateEvent
		: public BSTValueEvent<ViewCasterUpdateData> // 00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<ViewCasterUpdateEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::ViewCasterUpdateEvent::Singleton };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(sizeof(ViewCasterUpdateEvent) == 0x40);
}

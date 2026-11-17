#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/V/ViewCasterUpdateData.hpp"

namespace RE
{
	class ViewCasterUpdateEvent : public BSTValueEvent<ViewCasterUpdateData> // 0x00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<ViewCasterUpdateEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE = REL::Relocation<EventSourceType**>(ID::ViewCasterUpdateEvent::Singleton);
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(sizeof(ViewCasterUpdateEvent) == 0x40);
}

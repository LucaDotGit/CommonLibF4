#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CurrentRadiationSourceCount : public BSTValueEvent<std::uint32_t> // 0x00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<CurrentRadiationSourceCount>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::CurrentRadiationSourceCount::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(sizeof(CurrentRadiationSourceCount) == 0x08);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CurrentRadiationSourceCount
		: public BSTValueEvent<std::uint32_t> // 00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<CurrentRadiationSourceCount>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::CurrentRadiationSourceCount::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(sizeof(CurrentRadiationSourceCount) == 0x08);
}

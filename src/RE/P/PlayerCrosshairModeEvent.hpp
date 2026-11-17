#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class CrosshairMode : std::int32_t;

	class PlayerCrosshairModeEvent : public BSTValueEvent<CrosshairMode> // 0x00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PlayerCrosshairModeEvent>;

	public:
		[[nodiscard]]
		static auto GetEventSource() -> EventSourceType*
		{
			static const auto EVENT_SOURCE =
				REL::Relocation<EventSourceType**>{ID::PlayerCrosshairModeEvent::GetEventSource};
			if (!(*EVENT_SOURCE)) {
				*EVENT_SOURCE = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *EVENT_SOURCE;
		}
	};

	static_assert(sizeof(PlayerCrosshairModeEvent) == 0x08);
}

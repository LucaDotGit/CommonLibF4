#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class CrosshairMode : std::int32_t;

	class PlayerCrosshairModeEvent
		: public BSTValueEvent<CrosshairMode> // 00
	{
	private:
		using EventSourceType = BSTGlobalEvent::EventSource<PlayerCrosshairModeEvent>;

	public:
		[[nodiscard]] static EventSourceType* GetEventSource()
		{
			static const auto SINGLETON = REL::Relocation<EventSourceType**>{ ID::PlayerCrosshairModeEvent::GetEventSource };
			if (!*SINGLETON) {
				*SINGLETON = new EventSourceType(BSTGlobalEvent::GetSingleton()->eventSourceSDMKiller);
			}

			return *SINGLETON;
		}
	};
	static_assert(sizeof(PlayerCrosshairModeEvent) == 0x08);
}

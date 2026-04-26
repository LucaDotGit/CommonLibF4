#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::LocationMarkerArrayUpdate
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::LocationMarkerArrayUpdate::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		bool shouldClearMapMarkers; // 00
	};
	static_assert(sizeof(Event) == 0x01);
}

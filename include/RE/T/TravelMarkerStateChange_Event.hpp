#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class MapMarkerData;
}

namespace RE::TravelMarkerStateChange
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TravelMarkerStateChange::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle markerRef;		   // 00
		MapMarkerData* data;			   // 08
		std::uint32_t selectedMarkerIndex; // 10
		bool discovered;				   // 14
	};
	static_assert(sizeof(Event) == 0x18);
}

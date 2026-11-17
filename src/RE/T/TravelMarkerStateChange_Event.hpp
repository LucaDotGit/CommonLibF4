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
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TravelMarkerStateChange::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle markerRef;		   // 0x00
		MapMarkerData* data;			   // 0x08
		std::uint32_t selectedMarkerIndex; // 0x10
		bool discovered;				   // 0x14
	};

	static_assert(sizeof(Event) == 0x18);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PickRefUpdateEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<PickRefUpdateEvent>*
		{
			using FuncType = decltype(&PickRefUpdateEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PickRefUpdateEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle ref;		  // 0x00
		bool hasChanged;			  // 0x04
		bool activateDistanceChanged; // 0x05
		bool connectionTypeChanged;	  // 0x06
	};

	static_assert(sizeof(PickRefUpdateEvent) == 0x08);
}

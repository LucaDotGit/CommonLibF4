#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PickRefUpdateEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<PickRefUpdateEvent>* GetEventSource()
		{
			using FuncType = decltype(&PickRefUpdateEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PickRefUpdateEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle ref;		  // 00
		bool hasChanged;			  // 04
		bool activateDistanceChanged; // 05
		bool connectionTypeChanged;	  // 06
	};
	static_assert(sizeof(PickRefUpdateEvent) == 0x08);
}

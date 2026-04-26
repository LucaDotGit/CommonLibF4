#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESContainerChangedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESContainerChangedEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESContainerChangedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESContainerChangedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldContainerFormID; // 00
		TESFormID newContainerFormID; // 04
		TESFormID baseItemFormID;	  // 08
		std::uint32_t itemCount;	  // 0C
		TESFormID itemRefFormID;	  // 10
		ContainerID uniqueID;		  // 14
	};
	static_assert(sizeof(TESContainerChangedEvent) == 0x18);
}

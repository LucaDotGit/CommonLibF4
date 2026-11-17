#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESContainerChangedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESContainerChangedEvent>*
		{
			using FuncType = decltype(&TESContainerChangedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESContainerChangedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldContainerFormID; // 0x00
		TESFormID newContainerFormID; // 0x04
		TESFormID baseItemFormID;	  // 0x08
		std::uint32_t itemCount;	  // 0x0C
		TESFormID itemRefFormID;	  // 0x10
		ContainerID uniqueID;		  // 0x14
	};

	static_assert(sizeof(TESContainerChangedEvent) == 0x18);
}

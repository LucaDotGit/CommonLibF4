#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPickLockEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSPickLockEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;	   // 00
		ObjectRefHandle lockObjectRef; // 04
		std::uint32_t isCrime;		   // 08
	};
	static_assert(sizeof(BGSPickLockEvent) == 0x0C);
}

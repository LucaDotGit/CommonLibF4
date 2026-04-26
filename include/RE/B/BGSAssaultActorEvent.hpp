#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSAssaultActorEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSAssaultActorEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;	 // 00
		ObjectRefHandle attackerRef; // 04
		BGSLocation* location;		 // 08
		bool isCrime;				 // 10
	};
	static_assert(sizeof(BGSAssaultActorEvent) == 0x18);
}

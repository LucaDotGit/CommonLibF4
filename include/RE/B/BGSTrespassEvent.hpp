#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSTrespassEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSTrespassEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;	   // 00
		ObjectRefHandle trespasserRef; // 04
		BGSLocation* location;		   // 08
		bool isCrime;				   // 10
	};
	static_assert(sizeof(BGSTrespassEvent) == 0x18);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPickLockEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSPickLockEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;	   // 0x00
		ObjectRefHandle lockObjectRef; // 0x04
		std::uint32_t isCrime;		   // 0x08
	};

	static_assert(sizeof(BGSPickLockEvent) == 0x0C);
}

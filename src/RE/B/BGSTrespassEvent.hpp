#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSTrespassEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSTrespassEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef;	   // 0x00
		ObjectRefHandle trespasserRef; // 0x04
		BGSLocation* location;		   // 0x08
		bool isCrime;				   // 0x10
	};

	static_assert(sizeof(BGSTrespassEvent) == 0x18);
}

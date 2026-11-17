#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSArrestEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSArrestEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle guardRef;	 // 0x00
		ObjectRefHandle criminalRef; // 0x04
		BGSLocation* location;		 // 0x08
		std::int32_t crimeType;		 // 0x10
	};

	static_assert(sizeof(BGSArrestEvent) == 0x18);
}

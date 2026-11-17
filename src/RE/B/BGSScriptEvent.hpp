#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSScriptEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSScriptEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSKeyword* keyword;   // 0x00
		BGSLocation* location; // 0x08
		ObjectRefHandle ref01; // 0x10
		ObjectRefHandle ref02; // 0x14
		std::uint32_t value01; // 0x18
		std::uint32_t value02; // 0x1C
	};

	static_assert(sizeof(BGSScriptEvent) == 0x20);
}

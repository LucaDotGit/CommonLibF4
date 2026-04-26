#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSTriggerMineExplosionEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSTriggerMineExplosionEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef; // 00
		ObjectRefHandle mineRef;   // 04
	};
	static_assert(sizeof(BGSTriggerMineExplosionEvent) == 0x08);
}

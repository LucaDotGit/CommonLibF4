#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSTriggerMineExplosionEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX =
				REL::Relocation<std::uint32_t*>{ID::BGSTriggerMineExplosionEvent::EventIndex};
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle victimRef; // 0x00
		ObjectRefHandle mineRef;   // 0x04
	};

	static_assert(sizeof(BGSTriggerMineExplosionEvent) == 0x08);
}

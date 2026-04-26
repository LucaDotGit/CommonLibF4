#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDSubtitleDisplayData.hpp"

namespace RE
{
	class HUDSubtitleDisplayEvent
		: public BSTValueEvent<HUDSubtitleDisplayData> // 00
	{
	public:
	};
	static_assert(sizeof(HUDSubtitleDisplayEvent) == 0x18);
}

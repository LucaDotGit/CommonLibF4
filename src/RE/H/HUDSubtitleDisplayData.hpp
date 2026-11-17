#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDSubtitleDisplayData
	{
	public:
		// members
		BSFixedStringCS speakerName;  // 0x00
		BSFixedStringCS subtitleText; // 0x08
	};

	static_assert(sizeof(HUDSubtitleDisplayData) == 0x10);
}

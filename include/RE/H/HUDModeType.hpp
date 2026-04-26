#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDModeType
	{
	public:
		// members
		BSFixedString modeString; // 00
	};
	static_assert(sizeof(HUDModeType) == 0x08);
}

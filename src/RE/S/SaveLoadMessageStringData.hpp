#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class SaveLoadMessageStringData
	{
	public:
		// members
		BSFixedStringCS messageString; // 0x00
		BSFixedString soundIDString;   // 0x08
	};

	static_assert(sizeof(SaveLoadMessageStringData) == 0x10);
}

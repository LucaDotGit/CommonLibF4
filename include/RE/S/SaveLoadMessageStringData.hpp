#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class SaveLoadMessageStringData
	{
	public:
		// members
		BSFixedStringCS messageString; // 00
		BSFixedString soundIDString;   // 08
	};
	static_assert(sizeof(SaveLoadMessageStringData) == 0x10);
}

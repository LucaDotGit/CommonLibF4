#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSSaveLoadHistory
	{
	public:
		// members
		BSTArray<char*> notes; // 0x00
	};

	static_assert(sizeof(BGSSaveLoadHistory) == 0x18);
}

#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint
{
	class Entry;

	class Entries
	{
	public:
		// members
		BSTArray<Entry*> entries; // 00
	};
	static_assert(sizeof(Entries) == 0x18);
}

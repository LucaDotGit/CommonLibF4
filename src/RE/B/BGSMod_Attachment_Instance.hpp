#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BGSMod::Attachment
{
	class Instance
	{
	public:
		GAME_HEAP_REDEFINE_NEW(Instance);

		// members
		Mod* mod;					// 0x00
		std::uint8_t index;			// 0x08
		bool optional		   : 1; // 0x09:0
		bool childrenExclusive : 1; // 0x09:1
	};

	static_assert(sizeof(Instance) == 0x10);
}

#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BGSMod::Attachment
{
	class Instance // id == 0
	{
	public:
		GAME_HEAP_REDEFINE_NEW(Instance);

		// members
		Mod* mod;					// 00
		std::uint8_t index;			// 08
		bool optional		   : 1; // 09:0
		bool childrenExclusive : 1; // 09:1
	};
	static_assert(sizeof(Instance) == 0x10);
}

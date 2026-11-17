#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class PerkRankData
	{
	public:
		GAME_HEAP_REDEFINE_NEW(PerkRankData);

		// members
		BGSPerk* perk;			  // 0x00
		std::uint8_t currentRank; // 0x08
	};

	static_assert(sizeof(PerkRankData) == 0x10);
}

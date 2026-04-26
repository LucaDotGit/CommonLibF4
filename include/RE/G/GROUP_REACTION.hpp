#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	enum class FIGHT_REACTION : std::int32_t;

	class GROUP_REACTION
	{
	public:
		GAME_HEAP_REDEFINE_NEW(GROUP_REACTION);

		// members
		TESForm* form;										   // 00
		std::int32_t reaction;								   // 08
		REX::Enum<FIGHT_REACTION, std::int32_t> fightReaction; // 0C
	};
	static_assert(sizeof(GROUP_REACTION) == 0x10);
}

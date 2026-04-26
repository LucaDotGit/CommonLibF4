#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class MESSAGEBOX_BUTTON
	{
	public:
		GAME_HEAP_REDEFINE_NEW(MESSAGEBOX_BUTTON);

		// members
		BGSLocalizedString text; // 00
		TESCondition conditions; // 08
	};
	static_assert(sizeof(MESSAGEBOX_BUTTON) == 0x10);
}

#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	enum class QUEST_OBJECTIVE_STATE : std::int32_t;
	enum class QUEST_OBJECTIVE_FLAGS : std::int32_t;

	class TESQuestTarget;

	class BGSQuestObjective
	{
	public:
		GAME_HEAP_REDEFINE_NEW(BGSQuestObjective);

		// members
		BGSLocalizedString displayText;							  // 0x00
		TESQuest* ownerQuest;									  // 0x08
		SimpleArray<TESQuestTarget*> targets;					  // 0x10
		std::uint32_t numTargets;								  // 0x18
		std::uint16_t index;									  // 0x1C
		bool initialized;										  // 0x1E
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int8_t> state;	  // 0x1E
		REX::EnumSet<QUEST_OBJECTIVE_FLAGS, std::uint32_t> flags; // 0x20
	};

	static_assert(sizeof(BGSQuestObjective) == 0x28);
}

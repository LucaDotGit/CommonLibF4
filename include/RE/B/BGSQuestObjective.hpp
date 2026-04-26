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
		BGSLocalizedString displayText;							  // 00
		TESQuest* ownerQuest;									  // 08
		SimpleArray<TESQuestTarget*> targets;					  // 10
		std::uint32_t numTargets;								  // 18
		std::uint16_t index;									  // 1C
		bool initialized;										  // 1E
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int8_t> state;	  // 1E
		REX::EnumSet<QUEST_OBJECTIVE_FLAGS, std::uint32_t> flags; // 20
	};
	static_assert(sizeof(BGSQuestObjective) == 0x28);
}

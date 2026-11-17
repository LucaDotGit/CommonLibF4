#pragma once

namespace RE
{
	enum class QUEST_OBJECTIVE_STATE : std::int32_t;

	class BGSQuestObjective;

	class BGSInstancedQuestObjective
	{
	public:
		// members
		BGSQuestObjective* objective;								  // 0x00
		std::uint32_t instanceID;									  // 0x08
		REX::Enum<QUEST_OBJECTIVE_STATE, std::int32_t> enstanceState; // 0x0C
	};

	static_assert(sizeof(BGSInstancedQuestObjective) == 0x10);
}

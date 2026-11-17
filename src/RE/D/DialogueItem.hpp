#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class DialogueResponse;

	class DialogueItem
	{
	public:
		// members
		BSTArray<DialogueResponse*> responses;									  // 0x00
		TESTopicInfo* info;														  // 0x18
		TESTopic* topic;														  // 0x20
		TESQuest* quest;														  // 0x28
		TESObjectREFR* speaker;													  // 0x30
		std::uint32_t currentResponse{std::numeric_limits<std::uint32_t>::max()}; // 0x38
		bool endResponse;														  // 0x3C
		bool canSkip;															  // 0x3D
		bool subtitle;															  // 0x3E
	};

	static_assert(sizeof(DialogueItem) == 0x40);
}

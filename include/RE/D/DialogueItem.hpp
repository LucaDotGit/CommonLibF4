#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class DialogueResponse;

	class DialogueItem
	{
	public:
		// members
		BSTArray<DialogueResponse*> responses;										// 00
		TESTopicInfo* info;															// 18
		TESTopic* topic;															// 20
		TESQuest* quest;															// 28
		TESObjectREFR* speaker;														// 30
		std::uint32_t currentResponse{ std::numeric_limits<std::uint32_t>::max() }; // 38
		bool endResponse;															// 3C
		bool canSkip;																// 3D
		bool subtitle;																// 3E
	};
	static_assert(sizeof(DialogueItem) == 0x40);
}

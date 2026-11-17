#pragma once

#include "RE/B/BGSStoryManagerNodeBase.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class __declspec(novtable) BGSStoryManagerQuestNode : public BGSStoryManagerNodeBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerQuestNode;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerQuestNode;
		inline static constexpr auto FORM_TYPE = FormType::StoryManagerQuestNode;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				RunTime = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		// members
		BSTArray<TESQuest*> children;								 // 0x48
		BSTHashMap<TESQuest*, std::uint32_t> perQuestFlags;			 // 0x60
		BSTHashMap<TESQuest*, REX::Float32> perQuestHoursUntilReset; // 0x90
		std::uint32_t numQuestsToStart;								 // 0xC0
		BSTArray<REX::Float32> childrenLastRun;						 // 0xC8
	};

	static_assert(sizeof(BGSStoryManagerQuestNode) == 0xE0);
}

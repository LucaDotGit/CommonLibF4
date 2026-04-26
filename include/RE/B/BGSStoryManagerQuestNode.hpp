#pragma once

#include "RE/B/BGSStoryManagerNodeBase.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class __declspec(novtable) BGSStoryManagerQuestNode
		: public BGSStoryManagerNodeBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerQuestNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerQuestNode };
		inline static constexpr auto FORM_TYPE{ FormType::kStoryManagerQuestNode };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kRunTime = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		// members
		BSTArray<TESQuest*> children;								 // 48
		BSTHashMap<TESQuest*, std::uint32_t> perQuestFlags;			 // 60
		BSTHashMap<TESQuest*, REX::Float32> perQuestHoursUntilReset; // 90
		std::uint32_t numQuestsToStart;								 // C0
		BSTArray<REX::Float32> childrenLastRun;						 // C8
	};
	static_assert(sizeof(BGSStoryManagerQuestNode) == 0xE0);
}

#pragma once

#include "RE/B/BGSStoryManagerTreeForm.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class BGSStoryManagerBranchNode;

	class __declspec(novtable) BGSStoryManagerNodeBase
		: public BGSStoryManagerTreeForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerNodeBase };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerNodeBase };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		~BGSStoryManagerNodeBase() override; // 00

		// add
		virtual std::uint32_t GetQuestsStarted() const = 0; // 4E

		// members
		BGSStoryManagerBranchNode* parent;	  // 28
		BGSStoryManagerNodeBase* prevSibling; // 30
		std::uint32_t maxQuests;			  // 38
		std::uint32_t flags;				  // 3C
		TESCondition conditions;			  // 40
	};
	static_assert(sizeof(BGSStoryManagerNodeBase) == 0x48);
}

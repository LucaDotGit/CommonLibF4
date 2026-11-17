#pragma once

#include "RE/B/BGSStoryManagerTreeForm.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class BGSStoryManagerBranchNode;

	class __declspec(novtable) BGSStoryManagerNodeBase : public BGSStoryManagerTreeForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerNodeBase;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerNodeBase;
		inline static constexpr auto FORM_TYPE = FormType::None;

		~BGSStoryManagerNodeBase() override; // 0x00

		// add
		virtual auto GetQuestsStarted() const -> std::uint32_t = 0; // 0x4E

		// members
		BGSStoryManagerBranchNode* parent;	  // 0x28
		BGSStoryManagerNodeBase* prevSibling; // 0x30
		std::uint32_t maxQuests;			  // 0x38
		std::uint32_t flags;				  // 0x3C
		TESCondition conditions;			  // 0x40
	};

	static_assert(sizeof(BGSStoryManagerNodeBase) == 0x48);
}

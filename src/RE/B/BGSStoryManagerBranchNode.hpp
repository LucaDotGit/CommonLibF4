#pragma once

#include "RE/B/BGSStoryManagerNodeBase.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSStoryManagerBranchNode : public BGSStoryManagerNodeBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerBranchNode;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerBranchNode;
		inline static constexpr auto FORM_TYPE = FormType::StoryManagerBranchNode;

		// members
		BSTArray<BGSStoryManagerNodeBase*> children; // 0x48
	};

	static_assert(sizeof(BGSStoryManagerBranchNode) == 0x60);
}

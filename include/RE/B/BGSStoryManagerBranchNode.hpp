#pragma once

#include "RE/B/BGSStoryManagerNodeBase.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSStoryManagerBranchNode
		: public BGSStoryManagerNodeBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerBranchNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerBranchNode };
		inline static constexpr auto FORM_TYPE{ FormType::kStoryManagerBranchNode };

		// members
		BSTArray<BGSStoryManagerNodeBase*> children; // 48
	};
	static_assert(sizeof(BGSStoryManagerBranchNode) == 0x60);
}

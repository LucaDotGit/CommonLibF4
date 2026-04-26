#pragma once

#include "RE/B/BGSStoryManagerBranchNode.hpp"

namespace RE
{
	class BGSRegisteredStoryEvent;

	class __declspec(novtable) BGSStoryManagerEventNode
		: public BGSStoryManagerBranchNode // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerEventNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerEventNode };
		inline static constexpr auto FORM_TYPE{ FormType::kStoryManagerEventNode };

		// members
		BGSRegisteredStoryEvent* event; // 60
	};
	static_assert(sizeof(BGSStoryManagerEventNode) == 0x68);
}

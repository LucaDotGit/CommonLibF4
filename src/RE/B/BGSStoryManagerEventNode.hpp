#pragma once

#include "RE/B/BGSStoryManagerBranchNode.hpp"

namespace RE
{
	class BGSRegisteredStoryEvent;

	class __declspec(novtable) BGSStoryManagerEventNode : public BGSStoryManagerBranchNode // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryManagerEventNode;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryManagerEventNode;
		inline static constexpr auto FORM_TYPE = FormType::StoryManagerEventNode;

		// members
		BGSRegisteredStoryEvent* event; // 0x60
	};

	static_assert(sizeof(BGSStoryManagerEventNode) == 0x68);
}

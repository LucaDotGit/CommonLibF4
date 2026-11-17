#pragma once

#include "RE/B/BGSSceneActionConversationBase.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionPlayerDialogue : public BGSSceneActionConversationBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionPlayerDialogue;
		inline static constexpr auto VTABlE = VTABLE::BGSSceneActionPlayerDialogue;

		~BGSSceneActionPlayerDialogue() override; // 0x00

		[[nodiscard]]
		auto GetCurrentTopicInfo(BGSScene* a_parentScene, TESObjectREFR* a_target, std::uint32_t a_type)
			-> TESTopicInfo*
		{
			using FuncType = decltype(&BGSSceneActionPlayerDialogue::GetCurrentTopicInfo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSceneActionPlayerDialogue::GetCurrentTopicInfo);
			return std::invoke(FUNC, this, a_parentScene, a_target, a_type);
		}

		// members
		std::uint64_t dialogueTarget;							// 0x90
		std::array<TESTopic*, 4> pNPCResponseTopics;			// 0x98
		std::array<BGSKeyword*, 4> pNPCResponseSubtypeKeywords; // 0xB8
		TESTopic* pTopic;										// 0xD8
		std::uint32_t playerInput;								// 0xE0
	};

	static_assert(sizeof(BGSSceneActionPlayerDialogue) == 0xE8);
}

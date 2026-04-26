#pragma once

#include "RE/B/BGSSceneActionConversationBase.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionPlayerDialogue
		: public BGSSceneActionConversationBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionPlayerDialogue };
		inline static constexpr auto VTABlE{ VTABLE::BGSSceneActionPlayerDialogue };

		~BGSSceneActionPlayerDialogue() override; // 00

		[[nodiscard]] TESTopicInfo* GetCurrentTopicInfo(BGSScene* a_parentScene, TESObjectREFR* a_target, std::uint32_t a_type)
		{
			using FuncType = decltype(&BGSSceneActionPlayerDialogue::GetCurrentTopicInfo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSceneActionPlayerDialogue::GetCurrentTopicInfo };
			return std::invoke(FUNC, this, a_parentScene, a_target, a_type);
		}

		// members
		std::uint64_t dialogueTarget;							// 90
		std::array<TESTopic*, 4> pNPCResponseTopics;			// 98
		std::array<BGSKeyword*, 4> pNPCResponseSubtypeKeywords; // B8
		TESTopic* pTopic;										// D8
		std::uint32_t playerInput;								// E0
	};
	static_assert(sizeof(BGSSceneActionPlayerDialogue) == 0xE8);
}

#pragma once

#include "RE/B/BGSSceneActionConversationBase.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionNPCResponseDialogue
		: public BGSSceneActionConversationBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionNPCResponseDialogue };
		inline static constexpr auto VTABLE{ VTABLE::BGSSceneActionNPCResponseDialogue };

		~BGSSceneActionNPCResponseDialogue() override; // 00

		[[nodiscard]] TESTopicInfo* GetCurrentTopicInfo(BGSScene* a_parentScene)
		{
			using FuncType = decltype(&BGSSceneActionNPCResponseDialogue::GetCurrentTopicInfo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSceneActionNPCResponseDialogue::GetCurrentTopicInfo };
			return std::invoke(FUNC, this, a_parentScene);
		}
	};
	static_assert(sizeof(BGSSceneActionNPCResponseDialogue) == 0x90);
}

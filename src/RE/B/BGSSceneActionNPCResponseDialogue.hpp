#pragma once

#include "RE/B/BGSSceneActionConversationBase.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionNPCResponseDialogue : public BGSSceneActionConversationBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionNPCResponseDialogue;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSceneActionNPCResponseDialogue;

		~BGSSceneActionNPCResponseDialogue() override; // 0x00

		[[nodiscard]]
		auto GetCurrentTopicInfo(BGSScene* a_parentScene) -> TESTopicInfo*
		{
			using FuncType = decltype(&BGSSceneActionNPCResponseDialogue::GetCurrentTopicInfo);
			static const auto FUNC =
				REL::Relocation<FuncType>{ID::BGSSceneActionNPCResponseDialogue::GetCurrentTopicInfo};
			return std::invoke(FUNC, this, a_parentScene);
		}
	};

	static_assert(sizeof(BGSSceneActionNPCResponseDialogue) == 0x90);
}

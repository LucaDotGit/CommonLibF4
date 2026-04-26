#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionConversationBase
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionConversationBase };
		inline static constexpr auto VTABLE{ VTABLE::BGSSceneActionConversationBase };

		~BGSSceneActionConversationBase() override; // 00

		// members
		std::array<TESTopic*, 4> responseTopics;			 // 20
		std::array<BGSKeyword*, 4> pResponseSubtypeKeywords; // 40
		BGSSoundOutput* pOutputModel;						 // 60
		BSTArray<std::uint32_t> headTrackTargets;			 // 68
		std::uint32_t headTargetValue;						 // 80
		REX::Float32 headTrackChangeTimer;					 // 84
		TESTopic* currentTopic;								 // 88
	};
	static_assert(sizeof(BGSSceneActionConversationBase) == 0x90);
}

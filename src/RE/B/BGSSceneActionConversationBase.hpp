#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionConversationBase : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionConversationBase;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSceneActionConversationBase;

		~BGSSceneActionConversationBase() override; // 0x00

		// members
		std::array<TESTopic*, 4> responseTopics;			 // 0x20
		std::array<BGSKeyword*, 4> pResponseSubtypeKeywords; // 0x40
		BGSSoundOutput* pOutputModel;						 // 0x60
		BSTArray<std::uint32_t> headTrackTargets;			 // 0x68
		std::uint32_t headTargetValue;						 // 0x80
		REX::Float32 headTrackChangeTimer;					 // 0x84
		TESTopic* currentTopic;								 // 0x88
	};

	static_assert(sizeof(BGSSceneActionConversationBase) == 0x90);
}

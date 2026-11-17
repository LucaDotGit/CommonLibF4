#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionDialogue : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionDialogue;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSceneActionDialogue;

		~BGSSceneActionDialogue() override; // 0x00

		// members
		TESTopic* topic;								 // 0x20
		REX::Float32 maxLoopTime;						 // 0x28
		REX::Float32 minLoopTime;						 // 0x2C
		BSTArray<std::uint32_t> headTrackTargets;		 // 0x30
		REX::Float32 currentLoopTimer;					 // 0x48
		BGSKeyword* pAnimFaceArchType;					 // 0x50
		BGSKeyword* pSubtypeKeyword;					 // 0x58
		BGSSoundOutput* outputModel;					 // 0x60
		BSTSmartPointer<BSInputEnableLayer> pInputLayer; // 0x68
		std::uint32_t headTargetValue;					 // 0x74
		REX::Float32 headTrackChangeTimer;				 // 0x78
	};

	static_assert(sizeof(BGSSceneActionDialogue) == 0x78);
}

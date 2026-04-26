#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionDialogue
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionDialogue };
		inline static constexpr auto VTABLE{ VTABLE::BGSSceneActionDialogue };

		~BGSSceneActionDialogue() override; // 00

		// members
		TESTopic* topic;								 // 20
		REX::Float32 maxLoopTime;						 // 28
		REX::Float32 minLoopTime;						 // 2C
		BSTArray<std::uint32_t> headTrackTargets;		 // 30
		REX::Float32 currentLoopTimer;					 // 48
		BGSKeyword* pAnimFaceArchType;					 // 50
		BGSKeyword* pSubtypeKeyword;					 // 58
		BGSSoundOutput* outputModel;					 // 60
		BSTSmartPointer<BSInputEnableLayer> pInputLayer; // 68
		std::uint32_t headTargetValue;					 // 74
		REX::Float32 headTrackChangeTimer;				 // 78
	};
	static_assert(sizeof(BGSSceneActionDialogue) == 0x78);
}

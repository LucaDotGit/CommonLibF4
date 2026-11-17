#pragma once

#include "RE/B/BGSSceneAction.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionTimer : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionTimer;
		inline static constexpr auto VTABlE = VTABLE::BGSSceneActionTimer;

		~BGSSceneActionTimer() override; // 0x00

		// members
		REX::Float32 seconds;		 // 0x20
		REX::Float32 minSeconds;	 // 0x24
		REX::Float32 timer;			 // 0x28
		bool scriptEndRun;			 // 0x2C
		bool runEnd;				 // 0x2D
		REX::Float32 currentSeconds; // 0x30
	};

	static_assert(sizeof(BGSSceneActionTimer) == 0x38);
}

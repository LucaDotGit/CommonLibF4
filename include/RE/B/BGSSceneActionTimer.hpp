#pragma once

#include "RE/B/BGSSceneAction.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionTimer
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionTimer };
		inline static constexpr auto VTABlE{ VTABLE::BGSSceneActionTimer };

		~BGSSceneActionTimer() override; // 00

		// members
		REX::Float32 seconds;		 // 20
		REX::Float32 minSeconds;	 // 24
		REX::Float32 timer;			 // 28
		bool scriptEndRun;			 // 2C
		bool runEnd;				 // 2D
		REX::Float32 currentSeconds; // 30
	};
	static_assert(sizeof(BGSSceneActionTimer) == 0x38);
}

#pragma once

#include "RE/T/TESCondition.hpp"

namespace RE
{
	class BGSScenePhase
	{
	public:
		// members
		TESCondition startConditions;	   // 0x00
		TESCondition completionConditions; // 0x08
		std::uint16_t phaseFlags{0};	   // 0x10
		bool active{false};				   // 0x12
		bool scriptEndRun{false};		   // 0x13
		bool runEnd{false};				   // 0x14
	};

	static_assert(sizeof(BGSScenePhase) == 0x18);
}

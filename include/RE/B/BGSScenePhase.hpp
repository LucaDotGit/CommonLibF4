#pragma once

#include "RE/T/TESCondition.hpp"

namespace RE
{
	class BGSScenePhase
	{
	public:
		// members
		TESCondition startConditions;	   // 00
		TESCondition completionConditions; // 08
		std::uint16_t phaseFlags{ 0 };	   // 10
		bool active{ false };			   // 12
		bool scriptEndRun{ false };		   // 13
		bool runEnd{ false };			   // 14
	};
	static_assert(sizeof(BGSScenePhase) == 0x18);
}

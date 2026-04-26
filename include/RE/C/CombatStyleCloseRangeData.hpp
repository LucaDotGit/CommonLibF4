#pragma once

namespace RE
{
	class CombatStyleCloseRangeData
	{
	public:
		// members
		REX::Float32 circleMult;			  // 00
		REX::Float32 fallbackMult;			  // 04
		REX::Float32 flankDistanceMult;		  // 08
		REX::Float32 stalkTimeMult;			  // 0C
		REX::Float32 chargeDistanceMult;	  // 10
		REX::Float32 flipThrowProbability;	  // 14
		REX::Float32 sprintChargeProbability; // 18
		REX::Float32 sideswipeProbability;	  // 1C
		REX::Float32 disengageProbability;	  // 20
		std::uint32_t throwMaxTargets;		  // 24
		REX::Float32 flankVarianceMult;		  // 28
	};
	static_assert(sizeof(CombatStyleCloseRangeData) == 0x2C);
}

#pragma once

namespace RE
{
	class CombatStyleCloseRangeData
	{
	public:
		// members
		REX::Float32 circleMult;			  // 0x00
		REX::Float32 fallbackMult;			  // 0x04
		REX::Float32 flankDistanceMult;		  // 0x08
		REX::Float32 stalkTimeMult;			  // 0x0C
		REX::Float32 chargeDistanceMult;	  // 0x10
		REX::Float32 flipThrowProbability;	  // 0x14
		REX::Float32 sprintChargeProbability; // 0x18
		REX::Float32 sideswipeProbability;	  // 0x1C
		REX::Float32 disengageProbability;	  // 0x20
		std::uint32_t throwMaxTargets;		  // 0x24
		REX::Float32 flankVarianceMult;		  // 0x28
	};

	static_assert(sizeof(CombatStyleCloseRangeData) == 0x2C);
}

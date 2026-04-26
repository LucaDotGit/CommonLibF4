#pragma once

namespace RE
{
	class CombatStyleLongRangeData
	{
	public:
		// members
		REX::Float32 strafeMult;	  // 00
		REX::Float32 adjustRangeMult; // 04
		REX::Float32 crouchMult;	  // 08
		REX::Float32 waitMult;		  // 0C
		REX::Float32 rangeMult;		  // 10
	};
	static_assert(sizeof(CombatStyleLongRangeData) == 0x14);
}

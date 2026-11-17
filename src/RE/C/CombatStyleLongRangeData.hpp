#pragma once

namespace RE
{
	class CombatStyleLongRangeData
	{
	public:
		// members
		REX::Float32 strafeMult;	  // 0x00
		REX::Float32 adjustRangeMult; // 0x04
		REX::Float32 crouchMult;	  // 0x08
		REX::Float32 waitMult;		  // 0x0C
		REX::Float32 rangeMult;		  // 0x10
	};

	static_assert(sizeof(CombatStyleLongRangeData) == 0x14);
}

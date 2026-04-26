#pragma once

namespace RE
{
	class CombatStyleFlightData
	{
	public:
		// members
		REX::Float32 hoverChance;		   // 00
		REX::Float32 diveBombChance;	   // 04
		REX::Float32 groundAttackChance;   // 08
		REX::Float32 hoverTimeMult;		   // 0C
		REX::Float32 groundAttackTimeMult; // 10
		REX::Float32 perchAttackChance;	   // 14
		REX::Float32 perchAttackTimeMult;  // 18
		REX::Float32 flyingAttackChance;   // 1C
	};
	static_assert(sizeof(CombatStyleFlightData) == 0x20);
}

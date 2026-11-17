#pragma once

namespace RE
{
	class CombatStyleFlightData
	{
	public:
		// members
		REX::Float32 hoverChance;		   // 0x00
		REX::Float32 diveBombChance;	   // 0x04
		REX::Float32 groundAttackChance;   // 0x08
		REX::Float32 hoverTimeMult;		   // 0x0C
		REX::Float32 groundAttackTimeMult; // 0x10
		REX::Float32 perchAttackChance;	   // 0x14
		REX::Float32 perchAttackTimeMult;  // 0x18
		REX::Float32 flyingAttackChance;   // 0x1C
	};

	static_assert(sizeof(CombatStyleFlightData) == 0x20);
}

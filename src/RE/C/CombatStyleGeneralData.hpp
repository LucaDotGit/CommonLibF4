#pragma once

namespace RE
{
	class CombatStyleGeneralData
	{
	public:
		// members
		REX::Float32 offensiveMult;		 // 0x00
		REX::Float32 defensiveMult;		 // 0x04
		REX::Float32 groupOffensiveMult; // 0x08
		REX::Float32 meleeScoreMult;	 // 0x0C
		REX::Float32 magicScoreMult;	 // 0x10
		REX::Float32 rangedScoreMult;	 // 0x14
		REX::Float32 shoutScoreMult;	 // 0x18
		REX::Float32 unarmedScoreMult;	 // 0x1C
		REX::Float32 staffScoreMult;	 // 0x20
		REX::Float32 avoidThreatChance;	 // 0x24
		REX::Float32 dodgeThreatChance;	 // 0x28
		REX::Float32 evadeThreatChance;	 // 0x2C
	};

	static_assert(sizeof(CombatStyleGeneralData) == 0x30);
}

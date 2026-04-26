#pragma once

namespace RE
{
	class CombatStyleGeneralData
	{
	public:
		// members
		REX::Float32 offensiveMult;		 // 00
		REX::Float32 defensiveMult;		 // 04
		REX::Float32 groupOffensiveMult; // 08
		REX::Float32 meleeScoreMult;	 // 0C
		REX::Float32 magicScoreMult;	 // 10
		REX::Float32 rangedScoreMult;	 // 14
		REX::Float32 shoutScoreMult;	 // 18
		REX::Float32 unarmedScoreMult;	 // 1C
		REX::Float32 staffScoreMult;	 // 20
		REX::Float32 avoidThreatChance;	 // 24
		REX::Float32 dodgeThreatChance;	 // 28
		REX::Float32 evadeThreatChance;	 // 2C
	};
	static_assert(sizeof(CombatStyleGeneralData) == 0x30);
}

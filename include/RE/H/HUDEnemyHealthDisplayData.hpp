#pragma once

#include "RE/B/BSFixedString.hpp"
namespace RE
{
	class HUDEnemyHealthDisplayData
	{
	public:
		// members
		BSFixedString targetName;	   // 00
		REX::Float32 enemyHealth;	   // 08
		REX::Float32 backgroundHealth; // 0C
		bool useHUDWarningColor;	   // 10
		bool showLegendaryIcon;		   // 11
		bool showSkullIcon;			   // 12
	};
	static_assert(sizeof(HUDEnemyHealthDisplayData) == 0x18);
}

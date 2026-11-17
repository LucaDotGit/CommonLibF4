#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDEnemyHealthDisplayData
	{
	public:
		// members
		BSFixedString targetName;	   // 0x00
		REX::Float32 enemyHealth;	   // 0x08
		REX::Float32 backgroundHealth; // 0x0C
		bool useHUDWarningColor;	   // 0x10
		bool showLegendaryIcon;		   // 0x11
		bool showSkullIcon;			   // 0x12
	};

	static_assert(sizeof(HUDEnemyHealthDisplayData) == 0x18);
}

#pragma once

#include "RE/N/NiColor.hpp"

namespace RE
{
	class GameColorData
	{
	public:
		// members
		NiColor gameplayHUDColor;			// 0x00
		NiColor playerSetColor;				// 0x0C
		NiColor powerArmorHUDColor;			// 0x18
		NiColor HUDWarningColor;			// 0x24
		NiColor HUDAltWarningColor;			// 0x30
		NiColor playerSetBackgroundColor;	// 0x3C
		NiColor powerArmorBackgroundColor;	// 0x48
		NiColor gameplayHUDBackgroundColor; // 0x54
	};

	static_assert(sizeof(GameColorData) == 0x60);
}

#pragma once

namespace RE
{
	enum class HUDColorTypes : std::int32_t
	{
		kNoColorMultiplier = 0,
		kMenuNoColorBackground = 1,
		kGameplayHUDColor = 2,
		kPlayerSetColor = 3,
		kPowerArmorColorOnly = 4,
		kWarningColor = 5,
		kAltWarningColor = 6,
		kCustomColor = 7,

		kTotal = 8
	};
}

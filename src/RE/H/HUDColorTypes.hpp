#pragma once

namespace RE
{
	enum class HUDColorTypes : std::int32_t
	{
		NoColorMultiplier = 0,
		MenuNoColorBackground = 1,
		GameplayHUDColor = 2,
		PlayerSetColor = 3,
		PowerArmorColorOnly = 4,
		WarningColor = 5,
		AltWarningColor = 6,
		CustomColor = 7,

		_Count = 8
	};
}

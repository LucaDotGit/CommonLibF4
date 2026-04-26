#pragma once

namespace RE
{
	enum class POWER_ARMOR_HUD_VISIBILITY_RULE : std::int32_t
	{
		kIgnoresPAHUDVisibility = 0,
		kOnlyWithPAHUDVisible = 1,
		kOnlyWithPAHUDNotVisible = 2
	};
}

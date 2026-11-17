#pragma once

namespace RE
{
	enum class POWER_ARMOR_HUD_VISIBILITY_RULE : std::int32_t
	{
		IgnoresPAHUDVisibility = 0,
		OnlyWithPAHUDVisible = 1,
		OnlyWithPAHUDNotVisible = 2
	};
}

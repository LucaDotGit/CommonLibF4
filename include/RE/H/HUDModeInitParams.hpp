#pragma once

namespace RE
{
	enum class POWER_ARMOR_HUD_VISIBILITY_RULE : std::int32_t;

	class HUDModeType;

	class HUDModeInitParams
	{
	public:
		// members
		HUDModeType* validHUDModes;															  // 00
		std::uint32_t numHUDModes;															  // 08
		REX::Enum<POWER_ARMOR_HUD_VISIBILITY_RULE, std::int32_t> powerArmorHUDVisibilityRule; // 0C
	};
	static_assert(sizeof(HUDModeInitParams) == 0x10);
}

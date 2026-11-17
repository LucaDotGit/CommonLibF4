#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/H/HUDModeType.hpp"

namespace RE
{
	enum class POWER_ARMOR_HUD_VISIBILITY_RULE : std::int32_t;

	class HUDModes
	{
	public:
		// members
		BSTArray<HUDModeType> validHUDModes;												  // 0x00
		REX::Enum<POWER_ARMOR_HUD_VISIBILITY_RULE, std::int32_t> powerArmorHUDVisibilityRule; // 0x18
		bool canBeVisible;																	  // 0x1C
	};

	static_assert(sizeof(HUDModes) == 0x20);
}

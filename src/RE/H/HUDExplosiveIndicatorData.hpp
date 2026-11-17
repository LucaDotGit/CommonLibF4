#pragma once

#include "RE/E/ExplosiveIndicatorType.hpp"

namespace RE
{
	class HUDExplosiveIndicatorData
	{
	public:
		// members
		REX::Enum<ExplosiveIndicatorType, std::int32_t> indicatorType; // 0x00
		REX::Float32 distanceSquared;								   // 0x04
		REX::Float32 angleToPlayer;									   // 0x08
	};

	static_assert(sizeof(HUDExplosiveIndicatorData) == 0x0C);
}

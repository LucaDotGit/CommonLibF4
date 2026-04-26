#pragma once

#include "RE/E/ExplosiveIndicatorType.hpp"

namespace RE
{
	class HUDExplosiveIndicatorData
	{
	public:
		// members
		REX::Enum<ExplosiveIndicatorType, std::int32_t> indicatorType; // 00
		REX::Float32 distanceSquared;								   // 04
		REX::Float32 angleToPlayer;									   // 08
	};
	static_assert(sizeof(HUDExplosiveIndicatorData) == 0x0C);
}

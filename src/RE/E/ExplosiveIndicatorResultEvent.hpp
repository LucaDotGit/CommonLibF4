#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDExplosiveIndicatorDataArray.hpp"

namespace RE
{
	class ExplosiveIndicatorResultEvent : public BSTValueEvent<HUDExplosiveIndicatorDataArray> // 0x00
	{
	public:
	};

	static_assert(sizeof(ExplosiveIndicatorResultEvent) == 0x20);
}

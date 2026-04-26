#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDDirectionalHitIndicatorDataArray.hpp"

namespace RE
{
	class DirectionalHitIndicatorResultEvent
		: public BSTValueEvent<HUDDirectionalHitIndicatorDataArray> // 00
	{
	public:
	};
	static_assert(sizeof(DirectionalHitIndicatorResultEvent) == 0x20);
}

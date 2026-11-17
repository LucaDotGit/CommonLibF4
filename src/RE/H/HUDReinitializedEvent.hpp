#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class HUDReinitializedEvent : public BSTValueEvent<bool> // 0x00
	{
	public:
	};

	static_assert(sizeof(HUDReinitializedEvent) == 0x02);
}

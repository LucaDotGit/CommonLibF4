#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CanDisplayNextHUDObjective
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(CanDisplayNextHUDObjective) == 0x02);
}

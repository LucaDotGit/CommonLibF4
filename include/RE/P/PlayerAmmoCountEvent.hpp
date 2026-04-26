#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PlayerAmmoCounts.hpp"

namespace RE
{
	class PlayerAmmoCountEvent
		: public BSTValueEvent<PlayerAmmoCounts> // 00
	{
	public:
	};
	static_assert(sizeof(PlayerAmmoCountEvent) == 0x0C);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PlayerWeaponReloadEvent
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(PlayerWeaponReloadEvent) == 0x02);
}

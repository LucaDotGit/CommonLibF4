#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ShowingPerkVaultBoyState
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(ShowingPerkVaultBoyState) == 0x02);
}

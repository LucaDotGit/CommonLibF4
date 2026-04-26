#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ShowingFeaturedItemVaultBoyEvent
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(ShowingFeaturedItemVaultBoyEvent) == 0x02);
}

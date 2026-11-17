#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ShowingFeaturedItemVaultBoyEvent : public BSTValueEvent<bool> // 0x00
	{
	public:
	};

	static_assert(sizeof(ShowingFeaturedItemVaultBoyEvent) == 0x02);
}

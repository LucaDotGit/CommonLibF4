#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/H/HUDPerkVaultBoyData.hpp"

namespace RE
{
	class HUDPerkVaultBoySwfDisplayEvent
		: public BSTValueEvent<HUDPerkVaultBoyData> // 00
	{
	public:
	};
	static_assert(sizeof(HUDPerkVaultBoySwfDisplayEvent) == 0x20);
}

#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class HUDQuestVaultBoySwfName
		: public BSTValueEvent<BSFixedString> // 00
	{
	public:
	};
	static_assert(sizeof(HUDQuestVaultBoySwfName) == 0x10);
}

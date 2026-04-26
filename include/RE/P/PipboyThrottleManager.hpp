#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class IPipboyThrottledValue;

	class PipboyThrottleManager
	{
	public:
		// members
		BSTHashMap<std::uint32_t, IPipboyThrottledValue*> valueMap; // 00
	};
	static_assert(sizeof(PipboyThrottleManager) == 0x30);
}

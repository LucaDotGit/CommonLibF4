#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class VATSForcedEnemyHealthPercentEvent
		: public BSTValueEvent<REX::Float32> // 00
	{
	public:
	};
	static_assert(sizeof(VATSForcedEnemyHealthPercentEvent) == 0x08);
}

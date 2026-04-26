#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class PlayerRadiationDamageData
	{
	public:
		// members
		BSTSmartPointer<ActiveEffect> effect; // 00
	};
	static_assert(sizeof(PlayerRadiationDamageData) == 0x08);
}

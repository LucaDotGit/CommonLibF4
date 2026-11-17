#pragma once

#include "RE/M/MovementData.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class PlayerControlsMovementData : public MovementData // 0x00
	{
	public:
		// members
		NiPoint3A targetAngle; // 0x30
	};

	static_assert(sizeof(PlayerControlsMovementData) == 0x40);
}

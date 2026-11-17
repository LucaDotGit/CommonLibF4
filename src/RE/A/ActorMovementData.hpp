#pragma once

#include "RE/M/MovementData.hpp"
#include "RE/M/MovementTweenerOutputData.hpp"

namespace RE
{
	class ActorMovementData
	{
	public:
		// members
		MovementData handlerData;			   // 0x00
		MovementTweenerOutputData tweenerData; // 0x30
	};

	static_assert(sizeof(ActorMovementData) == 0x50);
}

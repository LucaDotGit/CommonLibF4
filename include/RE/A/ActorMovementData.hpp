#pragma once

#include "RE/M/MovementData.hpp"
#include "RE/M/MovementTweenerOutputData.hpp"

namespace RE
{
	class ActorMovementData
	{
	public:
		// members
		MovementData handlerData;			   // 00
		MovementTweenerOutputData tweenerData; // 30
	};
	static_assert(sizeof(ActorMovementData) == 0x50);
}

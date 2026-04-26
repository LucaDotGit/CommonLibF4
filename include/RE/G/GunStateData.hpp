#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/A/AITimer.hpp"
#include "RE/B/bhkCollisionQueryResultHandle.hpp"

namespace RE
{
	class GunStateData
	{
	public:
		// members
		bhkCollisionQueryResultHandle collisionRequest; // 00
		AITimer updateTimer;							// 08
		AITimeStamp gunStateChangedTimeStamp;			// 10
	};
	static_assert(sizeof(GunStateData) == 0x18);
}

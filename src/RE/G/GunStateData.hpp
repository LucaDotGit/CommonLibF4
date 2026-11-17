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
		bhkCollisionQueryResultHandle collisionRequest; // 0x00
		AITimer updateTimer;							// 0x08
		AITimeStamp gunStateChangedTimeStamp;			// 0x10
	};

	static_assert(sizeof(GunStateData) == 0x18);
}

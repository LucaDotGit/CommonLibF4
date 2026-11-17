#pragma once

#include "RE/B/BSPathingLocation.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSPathingGoal
	{
	public:
		enum class GOAL_RADIUS_TYPE : std::int32_t
		{
			None = 0,
			Soft = 1,
			Hard = 2,
			Mask = 3
		};

		enum class GOAL_HEIGHT_TYPE : std::int32_t
		{
			None = 0,
			Fixed = 16,
			Mask = 16
		};

		// members
		NiPoint3 targetPoint;				// 0x00
		REX::Float32 targetAngleTolerance;	// 0x0C
		BSPathingLocation location;			// 0x10
		REX::Float32 zDelta;				// 0x40
		REX::Float32 goalRadius;			// 0x44
		REX::Float32 normalizedSpeedAtGoal; // 0x48
	};

	static_assert(sizeof(BSPathingGoal) == 0x50);
}

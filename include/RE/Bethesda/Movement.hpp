#pragma once

#include "RE/Bethesda/BSFixedString.hpp"

namespace RE::Movement
{
	struct SPEED_DIRECTIONS
	{
		enum SPEED_DIRECTION : std::uint32_t
		{
			kLeft,
			kRight,
			kForward,
			kBackward,
			kPitch,
			kRoll,
			kYaw,

			kTotal
		};
	};

	struct MaxSpeeds
	{
	public:
		enum
		{
			kStanding,
			kWalking,
			kRunning,
			kSprinting,

			kTotal
		};

		// members
		float speeds[SPEED_DIRECTIONS::kTotal][kTotal]; // 00
	};
	static_assert(sizeof(MaxSpeeds) == 0x70);

	struct TypeData
	{
	public:
		// members
		BSFixedString typeName; // 00
		MaxSpeeds defaultData;	// 08
		float floatHeight;		// 78
		float flightAngleGain;	// 7C
	};
	static_assert(sizeof(TypeData) == 0x80);
}

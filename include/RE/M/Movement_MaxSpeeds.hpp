#pragma once

#include "RE/M/Movement_SPEED_DIRECTIONS.hpp"

namespace RE::Movement
{
	class MaxSpeeds
	{
	public:
		enum class SpeedType : std::int32_t
		{
			kStanding = 0,
			kWalking = 1,
			kRunning = 2,
			kSprinting = 3,

			kTotal = 4
		};

		// members
		std::array<std::array<REX::Float32, std::to_underlying(SPEED_DIRECTION::kTotal)>, std::to_underlying(SpeedType::kTotal)> speeds; // 00
	};
	static_assert(sizeof(MaxSpeeds) == 0x70);
}

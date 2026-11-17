#pragma once

#include "RE/M/Movement_SPEED_DIRECTIONS.hpp"

namespace RE::Movement
{
	class MaxSpeeds
	{
	public:
		enum class SpeedType : std::int32_t
		{
			Standing = 0,
			Walking = 1,
			Running = 2,
			Sprinting = 3,

			_Count = 4
		};

		// members
		std::array<
			std::array<REX::Float32, std::to_underlying(SPEED_DIRECTION::_Count)>,
			std::to_underlying(SpeedType::_Count)>
			speeds; // 0x00
	};

	static_assert(sizeof(MaxSpeeds) == 0x70);
}

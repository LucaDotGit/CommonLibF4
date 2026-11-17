#pragma once

namespace RE
{
	enum class DifficultyLevel : std::int32_t
	{
		VeryEasy = 0,
		Low = 0,
		Easy = 1,
		Normal = 2,
		Hard = 3,
		VeryHard = 4,
		Survival = 5,
		TrueSurvival = 6,

		_Min = VeryEasy,
		_Max = TrueSurvival,

		_Count = _Max + 1
	};
}

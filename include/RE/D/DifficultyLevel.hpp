#pragma once

namespace RE
{
	enum class DifficultyLevel : std::int32_t
	{
		kVeryEasy = 0,
		kLow = 0,
		kEasy = 1,
		kNormal = 2,
		kHard = 3,
		kVeryHard = 4,
		kSurvival = 5,
		kTrueSurvival = 6,

		kMin = kVeryEasy,
		kMax = kTrueSurvival,

		kTotal = (kMax - kMin) + 1
	};
}

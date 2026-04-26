#pragma once

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t
	{
		kLover = 0,
		kAlly = 1,
		kConfidant = 2,
		kFriend = 3,
		kAcquaintance = 4,
		kRival = 5,
		kFoe = 6,
		kEnemy = 7,
		kArchnemesis = 8,

		kTotal = 9
	};
}

#pragma once

namespace RE
{
	enum class QUEST_TYPE : std::int32_t
	{
		kNone = 0,
		kMainQuest = 1,
		kBrotherhoodOfSteel = 2,
		kInstitute = 3,
		kMinutemen = 4,
		kRailroad = 5,
		kMiscellaneous = 6,
		kSideQuest = 7,
		kDLC01 = 8,
		kDLC02 = 9,
		kDLC03 = 10,

		kTotal = 11
	};
}

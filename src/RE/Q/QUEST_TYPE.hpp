#pragma once

namespace RE
{
	enum class QUEST_TYPE : std::int32_t
	{
		None = 0,
		MainQuest = 1,
		BrotherhoodOfSteel = 2,
		Institute = 3,
		Minutemen = 4,
		Railroad = 5,
		Miscellaneous = 6,
		SideQuest = 7,
		DLC01 = 8,
		DLC02 = 9,
		DLC03 = 10,

		_Count = 11
	};
}

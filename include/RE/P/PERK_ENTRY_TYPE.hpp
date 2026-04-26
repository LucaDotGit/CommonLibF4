#pragma once

namespace RE
{
	enum class PERK_ENTRY_TYPE : std::int32_t
	{
		kInvalid = -1,
		kQuest = 0,
		kAbility = 1,
		kEntryPoint = 2,

		kTotal = 3
	};
}

#pragma once

namespace RE
{
	enum class PERK_ENTRY_TYPE : std::int32_t
	{
		Invalid = -1,
		Quest = 0,
		Ability = 1,
		EntryPoint = 2,

		_Count = 3
	};
}

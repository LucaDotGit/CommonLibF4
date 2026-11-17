#pragma once

namespace RE
{
	enum class PACK_EVENT_ACTION_TYPE : std::int32_t
	{
		Begin = 0,
		End = 1,
		Change = 2,
		Patrol = 3,
		_Count = 4
	};
}

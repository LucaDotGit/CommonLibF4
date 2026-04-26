#pragma once

namespace RE
{
	enum class PACK_EVENT_ACTION_TYPE : std::int32_t
	{
		kBegin = 0,
		kEnd = 1,
		kChange = 2,
		kPatrol = 3,
		kTotal = 4
	};
}

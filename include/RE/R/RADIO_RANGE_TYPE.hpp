#pragma once

namespace RE
{
	enum class RADIO_RANGE_TYPE : std::int32_t
	{
		kRadius = 0,
		kEverywhere = 1,
		kWorldspace = 2,
		kLinkedInt = 3,
		kCurrentCell = 4
	};
}

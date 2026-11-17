#pragma once

namespace RE
{
	enum class RADIO_RANGE_TYPE : std::int32_t
	{
		Radius = 0,
		Everywhere = 1,
		Worldspace = 2,
		LinkedInt = 3,
		CurrentCell = 4
	};
}

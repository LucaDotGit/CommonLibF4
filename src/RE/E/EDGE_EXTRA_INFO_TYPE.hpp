#pragma once

namespace RE
{
	enum class EDGE_EXTRA_INFO_TYPE : std::int32_t
	{
		Invalid = -1,
		Portal = 0,
		LedgeUp = 1,
		LedgeDown = 2,
		EnableDisablePortal = 3
	};
}

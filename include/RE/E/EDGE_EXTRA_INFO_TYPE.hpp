#pragma once

namespace RE
{
	enum class EDGE_EXTRA_INFO_TYPE : std::int32_t
	{
		kInvalid = -1,
		kPortal = 0,
		kLedgeUp = 1,
		kLedgeDown = 2,
		kEnableDisablePortal = 3
	};
}

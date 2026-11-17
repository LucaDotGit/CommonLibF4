#pragma once

namespace RE
{
	enum class _D3DCMPFUNC : std::int32_t
	{
		None = 0,
		Never = 1,
		Less = 2,
		Equal = 3,
		LessEqual = 4,
		Greater = 5,
		NotEqual = 6,
		GreaterEqual = 7,
		Always = 8,
		Force_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}

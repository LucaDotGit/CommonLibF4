#pragma once

namespace RE
{
	enum class _D3DBLENDOP : std::int32_t
	{
		None = 0,
		Add = 1,
		Subtract = 2,
		RevSubtract = 3,
		Min = 4,
		Max = 5,
		Force_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}

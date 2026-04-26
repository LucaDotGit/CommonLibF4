#pragma once

namespace RE
{
	enum class _D3DBLENDOP : std::int32_t
	{
		kNone = 0,
		kAdd = 1,
		kSubtract = 2,
		kRevSubtract = 3,
		kMin = 4,
		kMax = 5,
		kForce_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}

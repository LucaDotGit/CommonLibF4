#pragma once

namespace RE
{
	enum class _D3DCMPFUNC : std::int32_t
	{
		kNone = 0,
		kNever = 1,
		kLess = 2,
		kEqual = 3,
		kLessEqual = 4,
		kGreater = 5,
		kNotEqual = 6,
		kGreaterEqual = 7,
		kAlways = 8,
		kForce_DWORD = std::numeric_limits<std::int32_t>::max()
	};
}

#pragma once

namespace RE::BGSMod::Property
{
	enum class OP : std::int32_t
	{
		kSet = 0,
		kMul = 1,
		kAnd = 1,
		kRem = 1,
		kAdd = 2,
		kOr = 2
	};
}

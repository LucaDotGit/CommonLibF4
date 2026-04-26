#pragma once

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t
	{
		kNone = 0,
		kHidden = 1 << 0,
		kConditional = 1 << 1,
		kDefault = 1 << 2,
		kCollapsedOnRef = 1 << 3,
		kCollapsedOnBase = 1 << 4,
		kMandatory = 1 << 5
	};
}

#pragma once

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t
	{
		None = 0,
		Hidden = 1 << 0,
		Conditional = 1 << 1,
		Default = 1 << 2,
		CollapsedOnRef = 1 << 3,
		CollapsedOnBase = 1 << 4,
		Mandatory = 1 << 5
	};
}

#pragma once

namespace RE
{
	enum class ImpactResult : std::int32_t
	{
		None = 0,
		Destroy = 1,
		Bounce = 2,
		Impale = 3,
		Stick = 4
	};
}

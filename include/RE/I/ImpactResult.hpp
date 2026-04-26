#pragma once

namespace RE
{
	enum class ImpactResult : std::int32_t
	{
		kNone = 0,
		kDestroy = 1,
		kBounce = 2,
		kImpale = 3,
		kStick = 4
	};
}

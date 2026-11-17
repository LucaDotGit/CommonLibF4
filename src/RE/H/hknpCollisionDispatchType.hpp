#pragma once

namespace RE
{
	enum class hknpCollisionDispatchType : std::int32_t
	{
		None = 0,
		Convex = 1,
		Composite = 2,
		DistanceField = 3,
		User = 4
	};
}

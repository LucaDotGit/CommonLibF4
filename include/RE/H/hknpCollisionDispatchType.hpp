#pragma once

namespace RE
{
	enum class hknpCollisionDispatchType : std::int32_t
	{
		kNone = 0,
		kConvex = 1,
		kComposite = 2,
		kDistanceField = 3,
		kUser = 4
	};
}

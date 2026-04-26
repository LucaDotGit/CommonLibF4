#pragma once

namespace RE
{
	class hknpCollisionQueryType
	{
	public:
		enum class Enum : std::int32_t
		{
			kUndefined = 0,
			kRayCast = 1,
			kShapeCast = 2,
			kPointQuery = 3,
			kGetClosestPoints = 4,
			kQueryAABB = 5
		};
	};
	static_assert(std::is_empty_v<hknpCollisionQueryType>);
}

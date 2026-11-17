#pragma once

namespace RE
{
	class hknpCollisionQueryType
	{
	public:
		enum class Enum : std::int32_t
		{
			Undefined = 0,
			RayCast = 1,
			ShapeCast = 2,
			PointQuery = 3,
			GetClosestPoints = 4,
			QueryAABB = 5
		};
	};

	static_assert(std::is_empty_v<hknpCollisionQueryType>);
}

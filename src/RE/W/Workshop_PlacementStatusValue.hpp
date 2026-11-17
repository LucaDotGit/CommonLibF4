#pragma once

namespace RE::Workshop
{
	enum class PlacementStatusValue : std::int32_t
	{
		NoEditItem = 0,
		ValidPlacement = 1,
		Floating = 2,
		Intersecting = 3,
		TerrainOnly = 4,
		WaterRestriction = 5,
		SplineTooLong = 6,
		OutsideBuildArea = 7,
		RedundantSpline = 8,
		AttachedSplineInvalid = 9,
		Unsupported = 10,
		MustSnap = 11,
		RadiusOverlap = 12,
		Timer = 13,
		ReasonCount = 14,

		_Count = 15
	};
}

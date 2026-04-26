#pragma once

namespace RE::Workshop
{
	enum class PlacementStatusValue : std::int32_t
	{
		kNoEditItem = 0,
		kValidPlacement = 1,
		kFloating = 2,
		kIntersecting = 3,
		kTerrainOnly = 4,
		kWaterRestriction = 5,
		kSplineTooLong = 6,
		kOutsideBuildArea = 7,
		kRedundantSpline = 8,
		kAttachedSplineInvalid = 9,
		kUnsupported = 10,
		kMustSnap = 11,
		kRadiusOverlap = 12,
		kTimer = 13,
		kReasonCount = 14,

		kTotal = 15
	};
}

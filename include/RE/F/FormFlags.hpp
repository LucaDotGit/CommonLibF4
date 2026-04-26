#pragma once

namespace RE
{
	enum class FormFlags : std::int32_t
	{
		kNone = 0,

		kNeverFades = 1 << 2,
		kPlayable = 1 << 2,

		kInitialized = 1 << 3,
		kNonOccluder = 1 << 4,
		kDeleted = 1 << 5,

		kHasTreeLOD = 1 << 6,
		kKnown = 1 << 6,

		kMustUpdate = 1 << 8,
		kMustUpdateAnims = 1 << 8,

		kHiddenFromLocalMap = 1 << 9,
		kOnLocalMap = 1 << 9,

		kPersistent = 1 << 10,

		kDisabled = 1 << 11,
		kUsedAsPlatform = 1 << 11,

		kIgnored = 1 << 12,

		kEmpty = 1 << 13,
		kPackInUseOnly = 1 << 13,

		kTemporary = 1 << 14,
		kPartialForm = 1 << 14,

		kHasDistantLOD = 1 << 15,
		kRestricted = 1 << 15,

		kRandomAnim = 1 << 16,
		kDangerous = 1 << 17,
		kCompressed = 1 << 18,

		kCannotWait = 1 << 19,
		kHasCurrents = 1 << 19,

		kDestroyed = 1 << 23,
		kIsMarker = 1 << 23,

		kObstacle = 1 << 25,
		kNavMeshGeneration_Filter = 1 << 26,
		kNavMeshGeneration_BoundingBox = 1 << 27,
		kChildCanUse = 1 << 29,
		kNavMeshGeneration_Ground = 1 << 30
	};
}

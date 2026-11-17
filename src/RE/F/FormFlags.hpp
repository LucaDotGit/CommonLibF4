#pragma once

namespace RE
{
	enum class FormFlags : std::int32_t
	{
		None = 0,

		NeverFades = 1 << 2,
		Playable = 1 << 2,

		Initialized = 1 << 3,
		NonOccluder = 1 << 4,
		Deleted = 1 << 5,

		HasTreeLOD = 1 << 6,
		Known = 1 << 6,

		MustUpdate = 1 << 8,
		MustUpdateAnims = 1 << 8,

		HiddenFromLocalMap = 1 << 9,
		OnLocalMap = 1 << 9,

		Persistent = 1 << 10,

		Disabled = 1 << 11,
		UsedAsPlatform = 1 << 11,

		Ignored = 1 << 12,

		Empty = 1 << 13,
		PackInUseOnly = 1 << 13,

		Temporary = 1 << 14,
		PartialForm = 1 << 14,

		HasDistantLOD = 1 << 15,
		Restricted = 1 << 15,

		RandomAnim = 1 << 16,
		Dangerous = 1 << 17,
		Compressed = 1 << 18,

		CannotWait = 1 << 19,
		HasCurrents = 1 << 19,

		Destroyed = 1 << 23,
		IsMarker = 1 << 23,

		Obstacle = 1 << 25,
		NavMeshGeneration_Filter = 1 << 26,
		NavMeshGeneration_BoundingBox = 1 << 27,
		ChildCanUse = 1 << 29,
		NavMeshGeneration_Ground = 1 << 30
	};
}

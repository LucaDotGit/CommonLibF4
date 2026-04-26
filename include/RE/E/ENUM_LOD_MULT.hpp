#pragma once

namespace RE
{
	enum class ENUM_LOD_MULT : std::int32_t
	{
		kNone = 0,
		kObjects = 1,
		kItems = 2,
		kActors = 3,
		kTrees = 4,
		kLandscape = 5,
		kDistantLOD = 6,
		kActorBodyPart = 7,
		kRenderedMenu = 8,
		kInvisible = 9,
		kSkyCell = 10
	};
}
